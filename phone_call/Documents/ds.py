import streamlit as st
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import io

from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier, RandomForestRegressor, GradientBoostingClassifier, GradientBoostingRegressor
from sklearn.linear_model import LogisticRegression, LinearRegression
from sklearn.cluster import KMeans
from sklearn.metrics import accuracy_score, r2_score, silhouette_score
from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.decomposition import PCA

# --- THEME STYLES ---
light_style = """
<style>
    body {
        background-color: #f0f2f6;
        color: #111;
    }
    .stButton>button {
        background-color: #4CAF50;
        color: white;
    }
</style>
"""

dark_style = """
<style>
    body {
        background-color: #121212;
        color: #eee;
    }
    .stButton>button {
        background-color: #1f7a1f;
        color: white;
    }
</style>
"""

# --- APP CONFIG ---
st.set_page_config(page_title="Smart Data Dashboard & ML Trainer", layout="wide")


# NAVIGATION
page = st.sidebar.selectbox("📂 Navigation", ["Upload & Filter", "Visualize", "ML Trainer"])

# --- SESSION STATE INIT ---
if 'df' not in st.session_state:
    st.session_state.df = None
if 'filtered_df' not in st.session_state:
    st.session_state.filtered_df = None

# --- Helper functions ---
def auto_target(df):
    for col in df.columns:
        if 2 <= df[col].nunique() <= 20:
            return col
    return df.columns[-1]

def preprocess(df, target=None):
    df = df.copy()
    for col in df.columns:
        if df[col].dtype == 'object' or df[col].dtype.name == 'category':
            df[col] = df[col].astype(str).fillna(df[col].mode()[0])
            df[col] = LabelEncoder().fit_transform(df[col])
        else:
            df[col] = df[col].fillna(df[col].median())
    if target:
        X = df.drop(columns=[target])
        y = df[target]
        return X, y
    else:
        return df

def plot_and_download_chart(df, chart_type, x_col=None, y_col=None, pie_col=None):
    fig, ax = plt.subplots(figsize=(7,5))
    if chart_type == "Scatter":
        sns.scatterplot(data=df, x=x_col, y=y_col, ax=ax)
    elif chart_type == "Bar":
        sns.barplot(data=df, x=x_col, y=y_col, ax=ax)
    elif chart_type == "Line":
        sns.lineplot(data=df, x=x_col, y=y_col, ax=ax)
    elif chart_type == "Pie":
        counts = df[pie_col].value_counts()
        ax.pie(counts, labels=counts.index, autopct='%1.1f%%')
        ax.axis("equal")
    else:
        st.error("Unsupported chart type!")
        return
    st.pyplot(fig)

    buf = io.BytesIO()
    fig.savefig(buf, format="png")
    buf.seek(0)
    st.download_button(
        label="📥 Download Chart as PNG",
        data=buf,
        file_name="chart.png",
        mime="image/png"
    )

# --- PAGE: UPLOAD & FILTER ---
if page == "Upload & Filter":
    st.title("📁 Upload & Filter Data")

    uploaded_file = st.file_uploader("Upload CSV file", type="csv")
    if uploaded_file:
        df = pd.read_csv(uploaded_file)
        st.session_state.df = df
        st.session_state.filtered_df = df.copy()

        st.subheader("🔍 Data Preview")
        st.dataframe(df.head())

        st.subheader("🔧 Multi-Column Filters")
        filter_cols = st.multiselect("Select columns to filter", df.columns.tolist())
        filter_values = {}

        filtered_df = df.copy()
        for col in filter_cols:
            options = df[col].dropna().unique().tolist()
            default = st.session_state.get(f"filter_{col}", options[0])
            val = st.selectbox(f"Filter `{col}`", options, index=options.index(default), key=f"filter_{col}")
            filter_values[col] = val
            filtered_df = filtered_df[filtered_df[col] == val]

        st.session_state.filtered_df = filtered_df

        st.success(f"✅ Filtered rows: {len(filtered_df)}")
        st.dataframe(filtered_df)

        with st.expander("📊 Data Summary", expanded=True):
             st.write("**Shape:**", filtered_df.shape)
             st.write("📊 Summary Statistics")
             st.dataframe(filtered_df.describe())
             st.write("**Missing Values:**")
             st.dataframe(filtered_df.isnull().sum().rename("Missing Count"))

        csv = filtered_df.to_csv(index=False).encode('utf-8')
        st.download_button("⬇️ Download Filtered CSV", data=csv, file_name="filtered_data.csv", mime="text/csv")

    else:
        st.info("Upload a CSV file to start.")

# --- PAGE: VISUALIZE ---
elif page == "Visualize":
    st.title("📊 Visualize Data")

    df = st.session_state.filtered_df if st.session_state.filtered_df is not None else st.session_state.df

    if df is None:
        st.warning("Please upload and filter your data first.")
    else:
        numeric_cols = df.select_dtypes(include=[np.number]).columns.tolist()
        categorical_cols = df.select_dtypes(include=['object', 'category']).columns.tolist()

        chart_type = st.selectbox("Select Chart Type", ["Line", "Bar", "Area", "Pie", "Histogram", "Scatter"])

        if chart_type in ["Line", "Bar", "Area", "Scatter"]:
            x_col = st.selectbox("X-axis", numeric_cols)
            y_col = st.selectbox("Y-axis", numeric_cols)
            if st.button("Generate Chart"):
                if chart_type == "Line":
                    st.line_chart(df.set_index(x_col)[y_col])
                elif chart_type == "Bar":
                    st.bar_chart(df.set_index(x_col)[y_col])
                elif chart_type == "Area":
                    st.area_chart(df.set_index(x_col)[y_col])
                elif chart_type == "Scatter":
                    fig, ax = plt.subplots()
                    ax.scatter(df[x_col], df[y_col], color='skyblue')
                    ax.set_xlabel(x_col)
                    ax.set_ylabel(y_col)
                    st.pyplot(fig)
                    # Download button
                    buf = io.BytesIO()
                    fig.savefig(buf, format="png")
                    buf.seek(0)
                    st.download_button(
                        label="📥 Download Scatter Chart",
                        data=buf,
                        file_name="scatter_chart.png",
                        mime="image/png"
                    )

        elif chart_type == "Pie":
            if categorical_cols:
                pie_col = st.selectbox("Select categorical column", categorical_cols)
                if st.button("Generate Pie Chart"):
                    fig, ax = plt.subplots()
                    counts = df[pie_col].value_counts()
                    ax.pie(counts, labels=counts.index, autopct="%1.1f%%")
                    ax.axis("equal")
                    st.pyplot(fig)

                    buf = io.BytesIO()
                    fig.savefig(buf, format="png")
                    buf.seek(0)
                    st.download_button(
                        label="📥 Download Pie Chart",
                        data=buf,
                        file_name="pie_chart.png",
                        mime="image/png"
                    )
            else:
                st.warning("No categorical columns available for Pie Chart.")

        elif chart_type == "Histogram":
            hist_col = st.selectbox("Select numeric column", numeric_cols)
            bins = st.slider("Bins", 5, 50, 10)
            if st.button("Generate Histogram"):
                fig, ax = plt.subplots()
                ax.hist(df[hist_col], bins=bins, color='lightgreen', edgecolor='black')
                ax.set_xlabel(hist_col)
                ax.set_ylabel("Frequency")
                st.pyplot(fig)

                buf = io.BytesIO()
                fig.savefig(buf, format="png")
                buf.seek(0)
                st.download_button(
                    label="📥 Download Histogram",
                    data=buf,
                    file_name="histogram.png",
                    mime="image/png"
                )

# --- PAGE: ML TRAINER ---
elif page == "ML Trainer":
    st.title("🧠 Smart ML Trainer")

    df = st.session_state.filtered_df if st.session_state.filtered_df is not None else st.session_state.df

    if df is None:
        st.info("Upload and filter dataset first on 'Upload & Filter' page.")
    else:
        st.write("### 🔍 Data Preview")
        st.dataframe(df.head())

        numeric_cols = df.select_dtypes(include=[np.number]).columns.tolist()
        categorical_cols = df.select_dtypes(include=['object', 'category']).columns.tolist()

        def preprocess_ml(df, target=None):
            df = df.copy()
            for col in df.columns:
                if df[col].dtype == 'object' or df[col].dtype.name == 'category':
                    df[col] = df[col].astype(str).fillna(df[col].mode()[0])
                    df[col] = LabelEncoder().fit_transform(df[col])
                else:
                    df[col] = df[col].fillna(df[col].median())
            if target:
                X = df.drop(columns=[target])
                y = df[target]
                return X, y
            else:
                return df

        def auto_target_col(df):
            for col in df.columns:
                if 2 <= df[col].nunique() <= 20:
                    return col
            return df.columns[-1]

        target = st.selectbox("🎯 Select Target Column", df.columns, index=df.columns.get_loc(auto_target_col(df)))

        X, y = preprocess_ml(df, target)
        task_type = "Classification" if y.nunique() <= 20 else "Regression"
        st.info(f"Detected: *{task_type}* Problem")

        models = []
        if task_type == "Classification":
            models = [
                ("Random Forest", RandomForestClassifier(random_state=42)),
                ("Gradient Boosting", GradientBoostingClassifier(random_state=42)),
                ("Logistic Regression", LogisticRegression(max_iter=5000)),
            ]
        else:
            models = [
                ("Random Forest", RandomForestRegressor(random_state=42)),
                ("Gradient Boosting", GradientBoostingRegressor(random_state=42)),
                ("Linear Regression", LinearRegression()),
            ]

        if st.button("🚀 Train & Evaluate Models"):
            X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

            best_score = -np.inf
            best_model_name = None
            best_pred = None
            scores = {}

            for name, model in models:
                try:
                    model.fit(X_train, y_train)
                    pred = model.predict(X_test)
                    if task_type == "Classification":
                        score = accuracy_score(y_test, pred)
                    else:
                        score = r2_score(y_test, pred)
                    scores[name] = score
                    if score > best_score:
                        best_score = score
                        best_model_name = name
                        best_pred = pred
                except Exception as e:
                    st.warning(f"Model {name} failed: {e}")

            if best_model_name:
                st.success(f"✅ Best Model: *{best_model_name}* with score: {best_score:.3f}")

                st.write("### 🔍 Sample Predictions")
                result_df = X_test.copy()
                result_df["Actual"] = y_test.values
                result_df["Predicted"] = best_pred
                st.dataframe(result_df.head(10))

                st.write("### 📈 Prediction vs Actual Graph")
                fig, ax = plt.subplots(figsize=(8,5))
                ax.plot(result_df["Actual"].values[:20], label="Actual", marker='o')
                ax.plot(result_df["Predicted"].values[:20], label="Predicted", marker='x')
                ax.legend()
                st.pyplot(fig)

                buf = io.BytesIO()
                fig.savefig(buf, format="png")
                buf.seek(0)
                st.download_button(
                    label="📥 Download Prediction Graph as PNG",
                    data=buf,
                    file_name="prediction_chart.png",
                    mime="image/png"
                )

                st.write("### 📊 Model Performance Comparison")
                fig2, ax2 = plt.subplots(figsize=(7,4))
                model_names = list(scores.keys())
                model_scores = list(scores.values())
                colors = sns.color_palette("viridis", len(model_names))
                sns.barplot(x=model_names, y=model_scores, palette=colors, ax=ax2)
                if task_type == "Classification":
                    ax2.set_ylabel("Accuracy")
                else:
                    ax2.set_ylabel("R2 Score")
                ax2.set_ylim(0,1)
                st.pyplot(fig2)

                buf2 = io.BytesIO()
                fig2.savefig(buf2, format="png")
                buf2.seek(0)
                st.download_button(
                    label="📥 Download Model Performance Chart as PNG",
                    data=buf2,
                    file_name="model_performance.png",
                    mime="image/png"
                )
            else:
                st.error("Training failed for all models.")

        st.markdown("---")
        st.markdown("## 🌀 Unsupervised Learning (Clustering)")
        with st.expander("⚙ KMeans Clustering"):
            X_unsup = preprocess_ml(df)
            clusters = st.slider("🔢 Number of Clusters (K)", 2, 10, 3)

            if st.button("📍 Run Clustering"):
                scaler = StandardScaler()
                X_scaled = scaler.fit_transform(X_unsup)

                model = KMeans(n_clusters=clusters, random_state=42)
                labels = model.fit_predict(X_scaled)
                sil_score = silhouette_score(X_scaled, labels)

                df["Cluster"] = labels
                st.success(f"🧩 Clustering Done! Silhouette Score: {sil_score:.2f}")
                st.dataframe(df.head(10))

                st.write("### 🖼 Cluster Graph (via PCA)")
                pca = PCA(n_components=2)
                reduced = pca.fit_transform(X_scaled)
                cluster_df = pd.DataFrame(reduced, columns=["PC1", "PC2"])
                cluster_df["Cluster"] = labels

                fig, ax = plt.subplots(figsize=(8,5))
                sns.scatterplot(data=cluster_df, x="PC1", y="PC2", hue="Cluster", palette="Set2", ax=ax)
                st.pyplot(fig)

                buf = io.BytesIO()
                fig.savefig(buf, format="png")
                buf.seek(0)
                st.download_button(
                    label="📥 Download Cluster Graph as PNG",
                    data=buf,
                    file_name="cluster_chart.png",
                    mime="image/png"
                )
