import subprocess

treasure_types = ["book", "cube", "key"]
treasure_exists = {treasure: False for treasure in treasure_types}
with open("C:\\Users\\liuyilai\\Desktop\\testWeb\\resource\\output.log", "w") as log_file:
    process = subprocess.Popen(["python", "demo.py"], stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                               universal_newlines=True)

    try:
        for line in process.stdout:
            if line.startswith("0:"):
                log_file.write(line)
                if 'book' in line:
                    treasure_exists['book'] = True
                if 'cube' in line:
                    treasure_exists['cube'] = True
                if 'key' in line:
                    treasure_exists['key'] = True

    except KeyboardInterrupt:
        log_file.write("detected treasures include:")
        for treasure, exists in treasure_exists.items():
            if exists:
                log_file.write(treasure+ ",")

    process.wait()
