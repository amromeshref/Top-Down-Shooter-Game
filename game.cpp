#include <GL/glut.h>
#include <cstdlib>    
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>


// Window dimensions
const int windowWidth = 800;
const int windowHeight = 600;

// Player properties
struct Player {
    float x = windowWidth / 2.0f;
    float y = windowHeight - 50.0f;
    float size = 20.0f;
    float speed = 5.0f;
} player;

// Bullet properties
struct Bullet {
    float x, y;
    float speed = 7.0f;
};
std::vector<Bullet> bullets;

// Enemy properties
struct Enemy {
    float x, y;
    float size = 20.0f;
    float speed = 2.0f;
};
std::vector<Enemy> enemies;

// Game state
bool keys[256] = {false};
int score = 0;

// Initialize OpenGL
void initOpenGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
}

// Draw a rectangle
void drawRectangle(float x, float y, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x - width / 2, y - height / 2);
    glVertex2f(x + width / 2, y - height / 2);
    glVertex2f(x + width / 2, y + height / 2);
    glVertex2f(x - width / 2, y + height / 2);
    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw player
    drawRectangle(player.x, player.y, player.size, player.size, 0.0f, 1.0f, 0.0f);

    // Draw bullets
    for (const auto& bullet : bullets) {
        drawRectangle(bullet.x, bullet.y, 5, 10, 1.0f, 1.0f, 0.0f);
    }

    // Draw enemies
    for (const auto& enemy : enemies) {
        drawRectangle(enemy.x, enemy.y, enemy.size, enemy.size, 1.0f, 0.0f, 0.0f);
    }

    // Display score
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(10, windowHeight - 20);
    std::string scoreText = "Score: " + std::to_string(score);
    for (char c : scoreText) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
    }

    glutSwapBuffers();
}

// Update game state
void update(int value) {
    // Move player
    if (keys['a'] && player.x - player.size / 2 > 0) player.x -= player.speed;
    if (keys['d'] && player.x + player.size / 2 < windowWidth) player.x += player.speed;
    if (keys['w'] && player.y + player.size / 2 < windowHeight) player.y += player.speed;
    if (keys['s'] && player.y - player.size / 2 > 0) player.y -= player.speed;

    // Move bullets
    for (auto& bullet : bullets) {
        bullet.y += bullet.speed;
    }
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) {
        return b.y > windowHeight;
    }), bullets.end());

    // Move enemies
    for (auto& enemy : enemies) {
        enemy.y -= enemy.speed;
    }
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& e) {
        return e.y < 0;
    }), enemies.end());

    // Check for collisions
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ) {
        bool bulletRemoved = false;
        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ) {
            float dx = bulletIt->x - enemyIt->x;
            float dy = bulletIt->y - enemyIt->y;
            float distance = std::sqrt(dx * dx + dy * dy);
            if (distance < enemyIt->size / 2) {
                enemyIt = enemies.erase(enemyIt);
                bulletIt = bullets.erase(bulletIt);
                bulletRemoved = true;
                score += 10;
                break;
            } else {
                ++enemyIt;
            }
        }
        if (!bulletRemoved) {
            ++bulletIt;
        }
    }

    // Spawn enemies
    if (rand() % 100 < 5) {
        Enemy enemy;
        enemy.x = rand() % windowWidth;
        enemy.y = windowHeight;
        enemies.push_back(enemy);
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// Keyboard handling
void keyboardDown(unsigned char key, int x, int y) {
    keys[key] = true;
    if (key == ' ') {
        Bullet bullet;
        bullet.x = player.x;
        bullet.y = player.y + player.size / 2;
        bullets.push_back(bullet);
    }
}

void keyboardUp(unsigned char key, int x, int y) {
    keys[key] = false;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Top-Down Shooter");

    initOpenGL();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}

