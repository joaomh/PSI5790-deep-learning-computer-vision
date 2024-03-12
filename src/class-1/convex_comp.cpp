#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// Função para encontrar vizinhos válidos de um pixel
vector<Point> getValidNeighbors(const Mat& image, int x, int y) {
    vector<Point> neighbors;
    if (x > 0 && image.at<uchar>(x - 1, y) == 0) // Esquerda
        neighbors.push_back(Point(x - 1, y));
    if (y > 0 && image.at<uchar>(x, y - 1) == 0) // Acima
        neighbors.push_back(Point(x, y - 1));
    return neighbors;
}

// Função para percorrer os pixels conectados a partir de um pixel inicial usando BFS
void bfs(const Mat& image, Mat& visited, int x, int y) {
    queue<Point> q;
    q.push(Point(x, y));
    visited.at<uchar>(x, y) = 255; // Marca como visitado
    while (!q.empty()) {
        Point current = q.front();
        q.pop();
        vector<Point> neighbors = getValidNeighbors(image, current.x, current.y);
        for (const auto & neighbor : neighbors) {
            if (visited.at<uchar>(neighbor) == 0) { // Se o vizinho não foi visitado
                q.push(neighbor);
                visited.at<uchar>(neighbor) = 255; // Marca como visitado
            }
        }
    }
}

// Função para contar o número de componentes conectados na imagem
int countConnectedComponents(const Mat& image) {
    Mat visited = Mat::zeros(image.size(), CV_8UC1);
    int numComponents = 0;
    for (int x = 0; x < image.rows; ++x) {
        for (int y = 0; y < image.cols; ++y) {
            if (image.at<uchar>(x, y) == 0 && visited.at<uchar>(x, y) == 0) { // Se o pixel é preto e não foi visitado
                bfs(image, visited, x, y); // Inicia uma nova busca BFS
                numComponents++; // Incrementa o contador de componentes conectados
            }
        }
    }
    return numComponents;
}

int main() {
    // Carrega a imagem
    Mat image = imread("letras.bmp", IMREAD_GRAYSCALE);

    // Verifica se a imagem foi carregada corretamente
    if (image.empty()) {
        cerr << "Erro ao carregar a imagem." << endl;
        return EXIT_FAILURE;
    }

    // Conta o número de componentes conectados
    int numComponents = countConnectedComponents(image);

    // Imprime o resultado
    cout << "Número de componentes conexos: " << numComponents << endl;

    return EXIT_SUCCESS;
}