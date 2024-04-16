#include <iostream>
#include <fstream>

int** create_arr(int rows) {
    int** arr = new int* [rows];
    for (int i = 0; i < rows; i++) {
        arr[i] = new int[rows];
    }
    return arr;
}

void delete_arr(int** arr, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    arr = nullptr;
}

bool dfs(int** arr, int vertex, int* visited, const int num_vertex, int prev) {

    visited[vertex - 1] = 1;

    for (int j = 0; j < num_vertex; j++) {
        if ((arr[vertex - 1][j] == 1) && (visited[j] != 1)) {
            prev = j + 1;
            dfs(arr, (j + 1), visited, num_vertex, prev);
        }
        else if ((arr[vertex - 1][j] == 1) && (visited[j] == 1) && (vertex != prev)) {
            return true;
        }
    }

    return false;
}

std::string is_cyclic(int** arr, const int num_vertex) {

    int* visited = new int[num_vertex] {0};
    std::string ans;

    for (int i = 0; i < num_vertex; i++) {
        if (visited[i] != 1) {
            if (dfs(arr, (i + 1), visited, num_vertex, 0)) {
                ans = "В графе есть цикл!";
                break;
            }
            else {
                ans = "В графе нет циклов";
            }
        } 
    }

    delete[] visited;

    return ans;
}


int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Russian");

    std::ifstream input_data("in.txt");

    if (input_data.is_open()) {

        int num_vertex;
        input_data >> num_vertex;
        int** adj_matrix = create_arr(num_vertex);

        for (int i = 0; i < num_vertex; i++) {
            for (int j = 0; j < num_vertex; j++) {
                input_data >> adj_matrix[i][j];
            }
        }

        std::cout << is_cyclic(adj_matrix, num_vertex) << std::endl;

        delete_arr(adj_matrix, num_vertex);
        
        input_data.close();
    }
    else {
        std::cout << "Ошибка! Не удалось открыть файл" << std::endl;
    }

    return 0;
}