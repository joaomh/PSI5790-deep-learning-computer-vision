import cv2
a = cv2.imread('mickey.bmp',0)
for l in range(a.shape[0]-1):
    for c in range(a.shape[1]-1):
        if (a[l, c] != a[l, c+1]) and (a[l, c] != a[l, c-1]):
            a[l, c] = a[l,c-1]
cv2.imshow("Original", cv2.imread('mickey.bmp',0))
cv2.imshow("Resultado", a)
cv2.waitKey(0)
cv2.destroyAllWindows()