import paramiko

def run_ssh_command(host, username, password, command):
    try:
        # Create SSH client
        ssh = paramiko.SSHClient()
        ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())

        # Connect to the host
        ssh.connect(hostname=host, username=username, password=password)
        print(f"✅ Connected to {host}")

        # Execute the command
        stdin, stdout, stderr = ssh.exec_command(command)

        # Read results
        output = stdout.read().decode()
        error = stderr.read().decode()

        # Display results
        if output:
            print("📤 Output:")
            print(output)
        if error:
            print("❌ Error:")
            print(error)

        ssh.close()
    except Exception as e:
        print(f"Connection failed: {e}")

# Example usage
if __name__ == "__main__":
    ip = "192.168.192.74"         # Replace with actual IP
    user = "root"       # Replace with actual username
    passwd = "redhat"     # Replace with actual password
    cmd = "ls "               # Replace with any Linux command

    run_ssh_command(ip, user, passwd, cmd)
