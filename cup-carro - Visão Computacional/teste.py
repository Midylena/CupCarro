import cv2
import numpy as np

# Carregar o modelo YOLO
net = cv2.dnn.readNet("yolov4-tiny.weights", "yolov4-tiny.cfg")

# Carregar nomes das classes
classes = []
with open("coco.names", "r") as f:
    classes = f.read().strip().split('\n')

# Carregar imagem
image = cv2.imread("image.jpg")
height, width = image.shape[:2]

# Definir classes a serem filtradas
classes_to_filter = ["bus", "person"]

# Preparar a imagem para detecção
blob = cv2.dnn.blobFromImage(image, scalefactor=1/255.0, size=(416, 416), swapRB=True, crop=False)
net.setInput(blob)

# Obter detecções
layer_names = net.getUnconnectedOutLayersNames()
outs = net.forward(layer_names)

# Processar detecções
for out in outs:
    for detection in out:
        scores = detection[5:]
        class_id = np.argmax(scores)
        confidence = scores[class_id]

        if confidence > 0.5 and classes[class_id] in classes_to_filter:
            # Calcular coordenadas da bounding box
            center_x = int(detection[0] * width)
            center_y = int(detection[1] * height)
            w = int(detection[2] * width)
            h = int(detection[3] * height)
            x = int(center_x - w / 2)
            y = int(center_y - h / 2)

            # Desenhar bounding box e texto
            cv2.rectangle(image, (x, y), (x + w, y + h), (0, 255, 0), 2)
            cv2.putText(image, classes[class_id], (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)

# Exibir imagem resultante
cv2.imshow("Filtered Objects", image)
cv2.waitKey(0)
cv2.destroyAllWindows()