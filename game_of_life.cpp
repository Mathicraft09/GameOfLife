#include "raylib.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <numeric>

using namespace std;

// --- Constantes pour la partie graphique ---
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;
const int CELL_SIZE = 10; // Taille d'une cellule en pixels (10x10)
const int MAX_ROWS = SCREEN_HEIGHT / CELL_SIZE;
const int MAX_COLS = SCREEN_WIDTH / CELL_SIZE;

// --- Votre logique corrigée ---

// Fonction pour convertir la position souris en coordonnées grille
map<string, int> get_grid_position(int pixel_x, int pixel_y, int cell_size)
{
    int col = pixel_x / cell_size;
    int row = pixel_y / cell_size;
    return {{"row", row}, {"col", col}};
}

// Vérifie si une position est dans la grille (version C++ corrigée)
bool is_valide_position(int row, int col, int max_rows, int max_cols)
{
    return (row >= 0 && row < max_rows && col >= 0 && col < max_cols);
}

// Compte les voisins vivants (passage par référence constante pour la performance)
int count_neighbors_2D(const vector<vector<int>> &grid, int row, int col)
{
    int somme = 0;
    int current_max_rows = grid.size();
    int current_max_cols = grid[0].size();

    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            if (dy == 0 && dx == 0)
                continue; // Ignore la cellule elle-même

            int neighbor_row = row + dy;
            int neighbor_col = col + dx;

            if (is_valide_position(neighbor_row, neighbor_col, current_max_rows, current_max_cols))
            {
                somme += grid[neighbor_row][neighbor_col];
            }
        }
    }
    return somme;
}

// Calcule la génération suivante (logique corrigée)
vector<vector<int>> next_generation_2D(const vector<vector<int>> &grid)
{
    int rows = grid.size();
    int cols = grid[0].size();
    vector<vector<int>> next_grid(rows, vector<int>(cols, 0));

    for (int dy = 0; dy < rows; dy++)
    {
        for (int dx = 0; dx < cols; dx++)
        {
            int num = count_neighbors_2D(grid, dy, dx);

            // Règle 1 : Une cellule vivante reste en vie si 2 ou 3 voisins.
            if (grid[dy][dx] == 1)
            {
                if (num == 2 || num == 3)
                {
                    next_grid[dy][dx] = 1;
                }
            }
            // Règle 2 : Une cellule morte naît si exactement 3 voisins.
            else
            {
                if (num == 3)
                {
                    next_grid[dy][dx] = 1;
                }
            }
        }
    }
    return next_grid;
}

// --- Main avec Raylib ---

int main()
{
    // Initialisation de la fenêtre Raylib
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Le Jeu de la Vie - Raylib");
    SetTargetFPS(60); // On tourne à 60 FPS pour la réactivité de la souris

    // Initialisation de la grille à vide (taille basée sur l'écran)
    vector<vector<int>> grid(MAX_ROWS, vector<int>(MAX_COLS, 0));

    // Variables d'état de la simulation
    bool isRunning = false;      // Met la simulation en pause au début
    float updateTimer = 0.0f;    // Timer pour contrôler la vitesse d'évolution
    float updateInterval = 0.1f; // Évolution toutes les 0.1 secondes (10Hz)
    int generationCount = 0;

    // Ajout d'un motif initial (Glider) pour le test
    if (MAX_ROWS > 10 && MAX_COLS > 10)
    {
        grid[1][2] = 1;
        grid[2][3] = 1;
        grid[3][1] = 1;
        grid[3][2] = 1;
        grid[3][3] = 1;
    }

    // Boucle de jeu principale
    while (!WindowShouldClose())
    {
        // --- 1. Gestion des Entrées (Inputs) ---

        // Espace : Pause/Lecture
        if (IsKeyPressed(KEY_SPACE))
            isRunning = !isRunning;

        // C : Effacer la grille
        if (IsKeyPressed(KEY_C))
        {
            grid = vector<vector<int>>(MAX_ROWS, vector<int>(MAX_COLS, 0));
            generationCount = 0;
            isRunning = false;
        }

        // Clic Souris (Gaucher ou maintenu) : Dessiner des cellules
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePos = GetMousePosition();
            map<string, int> gridPos = get_grid_position((int)mousePos.x, (int)mousePos.y, CELL_SIZE);

            if (is_valide_position(gridPos["row"], gridPos["col"], MAX_ROWS, MAX_COLS))
            {
                grid[gridPos["row"]][gridPos["col"]] = 1;
            }
        }
        // Clic Droit : Effacer des cellules
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            Vector2 mousePos = GetMousePosition();
            map<string, int> gridPos = get_grid_position((int)mousePos.x, (int)mousePos.y, CELL_SIZE);

            if (is_valide_position(gridPos["row"], gridPos["col"], MAX_ROWS, MAX_COLS))
            {
                grid[gridPos["row"]][gridPos["col"]] = 0;
            }
        }

        // --- 2. Mise à jour de la logique (Update) ---

        if (isRunning)
        {
            updateTimer += GetFrameTime(); // Ajoute le temps écoulé depuis la dernière image

            // Si le temps écoulé dépasse l'intervalle, on calcule la génération suivante
            if (updateTimer >= updateInterval)
            {
                grid = next_generation_2D(grid);
                generationCount++;
                updateTimer = 0.0f; // RAZ du timer
            }
        }

        // --- 3. Rendu Graphique (Draw) ---

        BeginDrawing();
        ClearBackground(RAYWHITE); // Fond blanc

        // Dessiner les cellules vivantes
        for (int r = 0; r < MAX_ROWS; r++)
        {
            for (int c = 0; c < MAX_COLS; c++)
            {
                if (grid[r][c] == 1)
                {
                    // Dessine un rectangle plein pour la cellule vivante
                    // CELL_SIZE - 1 permet de laisser une petite bordure pour le quadrillage
                    DrawRectangle(c * CELL_SIZE, r * CELL_SIZE, CELL_SIZE - 1, CELL_SIZE - 1, DARKGRAY);
                }
            }
        }

        // Dessiner le quadrillage (optionnel, pour la clarté)
        /*
        for (int i = 0; i < SCREEN_WIDTH; i += CELL_SIZE) DrawLine(i, 0, i, SCREEN_HEIGHT, LIGHTGRAY);
        for (int i = 0; i < SCREEN_HEIGHT; i += CELL_SIZE) DrawLine(0, i, SCREEN_WIDTH, i, LIGHTGRAY);
        */

        // Interface Utilisateur (UI)
        DrawRectangle(0, 0, SCREEN_WIDTH, 40, Fade(BLACK, 0.7f)); // Barre de menu semi-transparente

        string status = isRunning ? "En cours" : "Pause";
        Color statusColor = isRunning ? LIME : RED;
        DrawText(TextFormat("Status: %s", status.c_str()), 10, 10, 20, statusColor);
        DrawText(TextFormat("Gen: %d", generationCount), 200, 10, 20, RAYWHITE);
        DrawText("Controles: [Espace] Pause/Play | [C] Effacer | [Clic Gauche] Dessiner", 400, 12, 16, LIGHTGRAY);

        EndDrawing();
    }

    // Nettoyage et fermeture
    CloseWindow();

    return 0;
}

// int main()
// {
//     InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Le jeu de la vie");
//     SetTargetFPS(60);

//     vector<vector<int>> grid(MAX_ROWS, vector<int>(MAX_COLS, 0));

//     if (MAX_ROWS > 10 && MAX_COLS > 10)
//     {
//         grid[1][2] = 1;
//         grid[2][3] = 1;
//         grid[3][1] = 1;
//         grid[3][2] = 1;
//         grid[3][3] = 1;
//     }

//     float timer = 0.0f;
//     float intervalle = 0.1f;
//     bool isRunning = true;

//     while (!WindowShouldClose())
//     {
//         if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
//         {
//             Vector2 mousePos = GetMousePosition();
//             int col = mousePos.x / CELL_SIZE;
//             int row = mousePos.y / CELL_SIZE;

//             if (is_valide_position(row, col, MAX_ROWS, MAX_COLS))
//             {
//                 grid[row][col] = 1;
//             }
//         }

//         if (IsKeyPressed(KEY_SPACE))
//         {
//             isRunning = !isRunning;
//         }

//         if (isRunning)
//         {
//             timer += GetFrameTime();
//             if (timer >= intervalle)
//             {
//                 grid = next_generation_2D(grid);
//                 timer = 0.0f;
//             }
//         }

//         BeginDrawing();
//         ClearBackground(RAYWHITE);

//         for (int r = 0; r < MAX_ROWS; r++)
//         {
//             for (int c = 0; c < MAX_COLS; c++)
//             {
//                 if (grid[r][c] == 1)
//                 {
//                     DrawRectangle(c * CELL_SIZE, r * CELL_SIZE, CELL_SIZE - 1, CELL_SIZE - 1, DARKGRAY);
//                 }
//             }
//         }

//         EndDrawing();
//     }
//     CloseWindow();
//     return 0;
// }