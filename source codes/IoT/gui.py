import gradio as gr
from ultralytics import YOLO

model = YOLO('./best_final.pt')


def predict_objects(input_image):
    results = model.predict(input_image, conf=0.4)
    return results[0].plot()


interface = gr.Interface(fn=predict_objects, inputs="image", outputs="image")
interface.launch()