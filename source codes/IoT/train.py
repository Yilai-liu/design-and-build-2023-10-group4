from ultralytics import YOLO

model = YOLO('yolov8n.pt')
if __name__ == '__main__':
  model.train(
    data = r'C:\Users\zsf03\code\python\designbuild\v6\data.yaml',
    epochs = 12,
    imgsz = 640
  )
