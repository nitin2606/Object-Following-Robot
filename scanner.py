import cv2
import numpy as np
import matplotlib.pyplot as plt
import networkx as nx

threshold_area = 100

threshold_distance = 10

url = "http://10.42.0.131:4747/video"

# Capture an image using the phone's camera
cap = cv2.VideoCapture(0)  # Adjust the camera index as needed
ret, frame = cap.read()
cap.release()

# Process the image to detect the floor
# (You may need to experiment with different techniques based on your specific scenario)
gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
blur = cv2.GaussianBlur(gray, (5, 5), 0)
edges = cv2.Canny(blur, 50, 150)

# Find contours of the floor
contours, _ = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Extract objects lying on the floor
objects = []
for contour in contours:
    # Filter out small contours based on area
    if cv2.contourArea(contour) > threshold_area:
        # Extract bounding box coordinates
        x, y, w, h = cv2.boundingRect(contour)
        # Calculate center coordinates of the object
        center_x = x + w // 2
        center_y = y + h // 2
        objects.append((center_x, center_y))

# Create a graph using NetworkX
graph = nx.Graph()

# Add nodes to the graph
for i, obj in enumerate(objects):
    graph.add_node(i, pos=obj)


# Add edges based on spatial relationships
for i in range(len(objects)):
    for j in range(i + 1, len(objects)):
        dist = np.sqrt((objects[i][0] - objects[j][0]) ** 2 + (objects[i][1] - objects[j][1]) ** 2)
        if dist < threshold_distance:
            graph.add_edge(i, j)

# Plot the graph
plt.figure(figsize=(8, 8))
pos = nx.get_node_attributes(graph, 'pos')
nx.draw(graph, pos, with_labels=True, node_size=200, font_size=8)
plt.axis('equal')
plt.show()
