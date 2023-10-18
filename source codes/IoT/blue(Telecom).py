# Beijing University of Posts and Telecommunications, Telecommunication Engineering and Management, Class of '21, Liu Yilai
# Development Time: 2023/10/9 19:59
# Beijing University of Posts and Telecommunications, Telecommunication Engineering and Management, Class of '21, Liu Yilai
# Development Time: 2023/10/9 19:54
import bluetooth
import time
import select

# Specify the address or name of the Bluetooth device
target_device = "23:5B:4C:3E:21:10"
file_path = "C:\\Users\\liuyilai\\Desktop\\testWeb\\resource\\test.log"  # Replace with the path of the file to be overwritten
start_time = time.time()

try:
    # Try to connect to the Bluetooth device
    sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
    sock.connect((target_device, 1))  # Connect to RFCOMM channel 1 (usually used for serial data)

    # Start timing


    while True:
        # Use select to wait for data
        ready_to_read, _, _ = select.select([sock], [], [], 2.0)

        if ready_to_read:
            data = sock.recv(1024)
            if not data:
                print("No data received, connection might be closed")
                with open(file_path, 'w') as file:
                    # End timing
                    end_time = time.time() - 3  # Connection failure time is 2s

                    # Calculate the elapsed time
                    elapsed_time = end_time - start_time-20
                    elapsed_time =int(elapsed_time)  # Accurate to two decimal places
                    file.write("{}s".format(elapsed_time))
                    print("Bluetooth connection is closed.")
                break
            else:
                print("Received data:", data.decode("utf-8"))
        else:
            # Use getpeername to check the Bluetooth connection status
            try:
                peer_address = sock.getpeername()
                print("Bluetooth is still connected to", peer_address)
            except bluetooth.btcommon.BluetoothError:
                with open(file_path, 'w') as file:
                    # End timing
                    end_time = time.time() - 3  # Connection failure time is 2s

                    # Calculate the elapsed time
                    elapsed_time = end_time - start_time-20
                    elapsed_time = int(elapsed_time)  # Accurate to two decimal places
                    file.write("{}s".format(elapsed_time))
                    print("Bluetooth connection is closed.")
                break

except bluetooth.btcommon.BluetoothError as e:
    with open(file_path, 'w') as file:
        # End timing
        end_time = time.time() - 2  # Connection failure time is 2s

        # Calculate the elapsed time
        elapsed_time = end_time - start_time - 20
        elapsed_time = int(elapsed_time)  # Accurate to two decimal places
        file.write("{}s".format(elapsed_time))
    print("Bluetooth connection error:", e)

finally:
    sock.close()  # Close the connection
