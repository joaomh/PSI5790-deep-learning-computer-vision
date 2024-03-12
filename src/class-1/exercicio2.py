from collections import deque
import cv2
import numpy as np
def neighbors(pixel, width, height):
    x, y = pixel
    neighbors = []
    if x > 0:
        neighbors.append((x - 1, y))
    if x < width - 1:
        neighbors.append((x + 1, y))
    if y > 0:
        neighbors.append((x, y - 1))
    if y < height - 1:
        neighbors.append((x, y + 1))
    return neighbors

def busca_largura(image, visited, start_pixel):
    width, height = image.shape
    queue = deque([start_pixel])
    visited[start_pixel] = True
    while queue:
        current_pixel = queue.popleft()
        for neighbor in neighbors(current_pixel, width, height):
            if not visited[neighbor] and image[neighbor] == 0: 
                visited[neighbor] = True
                queue.append(neighbor)

def count_connected_components(image):
    image = cv2.imread(image,0)
    width, height = image.shape
    visited = {(x, y): False for x in range(width) for y in range(height)}
    count = 0
    for x in range(width):
        for y in range(height):
            if not visited[(x, y)] and image[x, y] == 0:
                busca_largura(image, visited, (x, y))
                count += 1
    return count

image = "letras.bmp"
count = count_connected_components(image)
print("componentes conexos:", count)
image = "c2.bmp"
count = count_connected_components(image)
print("componentes conexos:", count)
image = "c3.bmp"
count = count_connected_components(image)
print("componentes conexos:", count)