from ultralytics import YOLO
# from ultralytics.yolo.utils.benchmarks import benchmark
import cv2
import os
import bluetooth

# 蓝牙设备的地址
target_device = "23:5B:4C:3E:21:10"  # replace bluetooth MAC


# 创建蓝牙套接字
sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
sock.connect((target_device, 1))





# Load a model
# model = YOLO("yolov8n.yaml")  # build a new model from scratch
model = YOLO("best_final.pt")  # load a pretrained model (recommended for training)

# Use the model
# model.train(data="coco128.yaml", epochs=3,workers=0)  # train the model,workers=0 if windows
# metrics = model.val()  # evaluate model performance on the validation set
'''
results = model("bus.jpg")  # predict on an image
print(results)
# '''
# Create a directory to store the saved frames
output_dir = "output_frames"
os.makedirs(output_dir, exist_ok=True)

# img_path = "./image/"
# results = model.predict(img_path, save=True,conf=0.5) # device=0 by default, conf:置信度阈值
# results = model.predict(img_path,save=True,classes=[0,2],conf=0.5) # i.e. classes=0,classes=[0,3,4]

# save detection results *
#results = model.predict('image_results',save=True,save_txt=True,classes=0,conf=0.4)



# predict video
# video_path = "./video/1.mp4"
#cap = cv2.VideoCapture("http://192.168.8.1:8083/?action=snapshot")
cap = cv2.VideoCapture("http://192.168.8.1:8083/?action=stream")
# #http://192.168.8.1:8083/?action=stream
#http://192.168.8.1:8083/?action=stream
frame_count = 0
while cap.isOpened():
    # Read a frame from the video
    success, frame = cap.read()

    if success:
        # Run YOLOv8 inference on the frame
        results = model(frame)

        # Visualize the results on the frame
        annotated_frame = results[0].plot()

        if results[0] is not None and len(results[0]) > 0:
            # Save the frame as an image
            output_filename = os.path.join(output_dir, f"frame_{frame_count:04d}.jpg")
            cv2.imwrite(output_filename, annotated_frame)

            frame_count += 1
        # Display the annotated frame
        cv2.imshow("YOLOv8 Inference", annotated_frame)

        resultList = results[0].boxes.cls.cpu().numpy()

        if 0.0 in resultList:
            print("book detected")
        elif 1.0 in resultList:
            data_to_send = "1"
            sock.send(data_to_send)
            print("cube detected")
        elif 2.0 in resultList:
            data_to_send = "2"
            sock.send(data_to_send)
            print("key detected")

        # Break the loop if 'q' is pressed
        if cv2.waitKey(1) & 0xFF == ord("q"):
            break
    else:
        # Break the loop if the end of the video is reached
        break

# Release the video capture object and close the display window
cap.release()
cv2.destroyAllWindows()
"""       for detection in results.xyxy[0]:
           class_id, confidence, left, top, right, bottom = detection
           class_name = model.names[int(class_id)]

           if class_name == "key" and confidence > 0.5:
               pass
       # 调用函数
           if class_name == "cube" and confidence > 0.5:
               pass
       # 调用函数

       cv2.imshow("YOLOv8 Inference", annotated_frame)"""


"""        for detection in results.pandas().xyxy[0].values:
            class_id, confidence, left, top, right, bottom = detection
            class_name = model.names[int(class_id)]
            # 这里继续执行你的操作
            if class_name == "key" and confidence > 0.5:
                pass"""