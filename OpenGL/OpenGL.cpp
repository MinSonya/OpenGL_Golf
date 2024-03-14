#ifndef FILE_STUFF
#define FILE_STUFF
#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <math.h>
#include <ctime>
#include <glut.h>
using namespace std;
#endif


void glut_key_action(unsigned char key, int x, int y);//функция для обработки нажатия клавиш клавиатуры
void drawCircle(float x, float y, float radius); //функция для рисования лунки
void spinDisplay(void); //вращение мельницы
void timer(int id); //таймер для анимации
GLuint LoadTexture(const char* filename); //загрузка текстур
static void drawBox(GLfloat size, GLenum type, GLuint text); //рисования куба с текстурой
static void drawSimpleBox(GLfloat size, GLenum type);	//рисование куба

bool  windmillOn = false, ballOn = false, shootOn = false, snowmanOn = false;
bool translating = false, tAnimating = false;
const int milliseconds_per_frame = 10;
float angle = 0;
float spin = 0;
float snowSpin = 0;
float tx = 0;
float ty = 0;
int menu_id;

//два квадрик объекта
GLUquadricObj* q;
GLUquadricObj* ball; //мяч

//освещение
GLfloat light_color0[] = { 0.3f,0.3f,0.3f,1.0f };
GLfloat light_position0[] = { 0.0f, 0.0f, 13.0f, 1.0f };

//текстуры
GLuint textureGrass;
GLuint textureBrick;
GLuint textureSnow;

GLfloat color[4] = { 1.0, 0.0, 0.6, 1.0 };

void init(void)
{
	q = gluNewQuadric();//создаем сферы
	ball = gluNewQuadric();
	textureGrass = LoadTexture("grass.bmp");		//загружаем текстуры
	textureBrick = LoadTexture("brick.bmp");
	textureSnow = LoadTexture("snow.bmp");
	glClearColor(0.0, 0.0, 0.0, 0.0);//очистка экрана
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);

	int w = glutGet(GLUT_WINDOW_WIDTH); //ширина экрана
	int h = glutGet(GLUT_WINDOW_HEIGHT); //высота экрана
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 30.0);	//выставляем перспективу
	glMatrixMode(GL_MODELVIEW);

	//освещение
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_color0);
	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, light_color0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

	glEnable(GL_COLOR_MATERIAL);

}

void display(void)		//отрисовка объектов
{
	//if (tAnimating)//установка скорости для таймера
		//glutTimerFunc(milliseconds_per_frame, timer, 1);

	glRotatef(angle, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_LIGHTING);		//установка фонового освещения и источника света
	glEnable(GL_LIGHT0);

	//растение
	color[0] = 0.133333;
	color[1] = 0.545098;
	color[2] = 0.133333;
	color[3] = 0.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	glColor3f(0.133333, 0.545098, 0.133333);
	glPushMatrix();
	glTranslatef(1.25, -1.6, 2);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	gluCylinder(q, 0.05, 0.0, 3.0, 3, 3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.25, -1.6, 2);
	glRotatef(-90.0, 5.0, 1.0, 0.0);
	gluCylinder(q, 0.05, 0.0, 2.8, 3, 3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.25, -1.6, 2);
	glRotatef(220.0, 0.0, 1.0, 2.0);
	gluCylinder(q, 0.05, 0.0, 2.8, 3, 3); 
	glPopMatrix();


	//рисуем основание поля
	glPushMatrix();
	glTranslatef(0, 2, -4);
	glRotatef(-90, 1, 0, 0);
	glBegin(GL_POLYGON);
	glColor3f(0.439216, 0.501961, 0.564706);
	glVertex3f(-20, -20, -4.0);
	glVertex3f(20, -20.0, -4.0);
	glVertex3f(20, 20, -4.0);
	glVertex3f(-20, 20, -4.0);
	glEnd();
	glPopMatrix();


	//трава на поле
	glPushMatrix();
	glTranslatef(0, 2.4, -4);
	glRotatef(-90, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, textureGrass);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.5f, -10.0, -4.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.5f, -10.0, -4.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(1.5, 4, -4.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-1.5, 4, -4.0);
	glEnd();
	glPopMatrix();

	//бортики
	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(-1.7, -1.5, -1);
	glRotatef(90, 1, 0, 0);
	glScalef(1.5, 55, 1);
	drawSimpleBox(0.25, GL_QUADS);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.7, -1.5, -1);
	glRotatef(90, 1, 0, 0);
	glScalef(1.5, 55, 1);
	drawSimpleBox(0.25, GL_QUADS);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -1.5, -8);
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(1.5, 15.15, 1);
	drawSimpleBox(0.25, GL_QUADS);
	glPopMatrix();

	//лунка
	glPushMatrix();
	glTranslatef(-.75, -1.5, -6.25);
	glRotatef(90, 1, 0, 0);
	drawCircle(.8, .8, .2);
	glPopMatrix();

	//отрисовывется флаг, пока мяч не запустили. Когда мяч запускается, то флаг исчезает
	glPushMatrix();
	if (!(shootOn))
	{
		glTranslatef(0, 1l, -5.4);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		gluCylinder(q, 0.06, 0.06, 2.5, 15, 15);	//основание
	}
	glPopMatrix();
	glPushMatrix();
	if (!(shootOn))
	{
		glColor3f(1, 0, 0);
		glTranslatef(.3, .88, -5.35);
		glRotatef(90, 0, 1, 0);
		glRotatef(90, 0, 1, 0);
		glRotatef(90, 1, 0, 0);
		glScalef(2.5, .25, 1);
		drawSimpleBox(0.25, GL_QUADS);			//сам флаг
	}
	glPopMatrix();  

	//основание для снеговика и сам снеговик
	glColor3f(0.545098, 0.270588, 0.0745098);
	glPushMatrix();
	glTranslatef(-2.5, -1.5, 1);
	glScalef(1, .25, 1);
	glBindTexture(GL_TEXTURE_2D, textureBrick);
	drawBox(1.0, GL_QUADS, textureBrick);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.5, -1.3, 1);
	glScalef(1, .25, 1);
	glBindTexture(GL_TEXTURE_2D, textureBrick);
	drawBox(0.75, GL_QUADS, textureBrick);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.5, -1.1, 1);
	glScalef(1, .25, 1);
	glBindTexture(GL_TEXTURE_2D, textureBrick);
	drawBox(0.75, GL_QUADS, textureBrick);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.5, -.9, 1);
	glScalef(1, .25, 1);
	glBindTexture(GL_TEXTURE_2D, textureBrick);
	drawBox(0.75, GL_QUADS, textureBrick);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.5, -.7, 1);
	glScalef(1, .25, 1);
	glBindTexture(GL_TEXTURE_2D, textureBrick);
	drawBox(0.75, GL_QUADS, textureBrick);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.5, -.5, 1);
	glScalef(1, .25, 1);
	glBindTexture(GL_TEXTURE_2D, textureBrick);
	drawBox(0.75, GL_QUADS, textureBrick);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.5, -.3, 1);
	glScalef(1, .25, 1);
	glBindTexture(GL_TEXTURE_2D, textureBrick);
	drawBox(0.75, GL_QUADS, textureBrick);
	glPopMatrix(); 
	glPushMatrix();
	if (snowmanOn)			//если запущено вращение снеговика
	{
		glTranslatef(-2.5, -.07, 1);
		glRotatef(snowSpin, 0, 1, 0);
		glTranslatef(2.5, .07, -1);
	}
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-2.5, -.07, 1);
	gluSphere(q, 0.25, 20, 20);
	glTranslatef(0.0, 0.25, 0.0);
	gluSphere(q, 0.2, 20, 20);
	glTranslatef(0.0, 0.2, 0.0);
	gluSphere(q, 0.15, 20, 20);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.15, 0.05, 0.05);
	gluSphere(q, 0.01, 10, 10);
	glTranslatef(0.0, 0.0, -0.10);
	gluSphere(q, 0.01, 10, 10);
	glColor3f(1.0, 0.3, 0.0);
	glTranslatef(0.0, -0.05, 0.05);
	glRotatef(90, 0.0, 1.0, 0.0);
	gluCylinder(q, 0.02, 0.0, 0.1, 3, 3);
	glPopMatrix();
	glPopMatrix();


	//мельница
	glPushMatrix();
	glColor3f(0.823529, 0.705882, 0.54902);
	glTranslatef(0, -1.5, 0);
	glRotatef(45, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(q, 0.5, 0.0, 2.0, 4, 4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, .5, .1);
	glScalef(.1, .1, .1);
	gluSphere(q, 1, 10, 10);
	glPopMatrix();
	//вращение лопастей
	glPushMatrix();
	if (windmillOn)
	{
		glTranslatef(0, .5, .1);
		glRotatef(spin, 0, 0, 1);
		glTranslatef(0, -.5, -.1);
	}
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-.875, .5, .2);
	glRotatef(90, 0, 1, 0);
	glScalef(.15, 1, 1);
	gluCylinder(q, 0.25, 0.0, 0.9, 4, 4);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(.875, .5, .2);
	glRotatef(270, 0, 1, 0);
	glScalef(.15, 1, 1);
	gluCylinder(q, 0.25, 0.0, 0.9, 4, 4);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, -.4, .2);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glScalef(.15, 1, 1);
	gluCylinder(q, 0.25, 0.0, 0.9, 4, 4);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, 1.35, .2);
	glRotatef(270, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glScalef(.15, 1, 1);
	gluCylinder(q, 0.25, 0.0, 0.9, 4, 4);
	glPopMatrix();

	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -1.2, 3.75);
	glRotatef(10, 1, 0, 0);
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	glVertex3f(-.15, -1, -4);
	glVertex3f(.15, -1, -4);
	glVertex3f(.15, -.6, -4);
	glVertex3f(-.15, -.6, -4);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, .17, 4.13);
	glRotatef(-10, 1, 0, 0);
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 0);
	glVertex3f(-.15, -1, -4);
	glVertex3f(.15, -1, -4);
	glVertex3f(.15, -.6, -4);
	glVertex3f(-.15, -.6, -4);
	glEnd();
	glPopMatrix();

	//мяч
	glPushMatrix();
	if (tx <= -10.95 && ty <= 0.1 && ty >= -0.1) {
		shootOn = false;
		ballOn = false;
		tx = 0;
		ty = 0;
	}
	if (shootOn)
	{
		glTranslatef(ty, 0, tx);
	}
	glPushMatrix();
	if (ballOn)
	{
		glColor3f(1, 1, 1);
		glTranslatef(0, -1.5, 5.5);
		gluSphere(ball, .05, 10, 10);
	}
	glPopMatrix();
	glPopMatrix(); 
	
	//анимация
	glutSwapBuffers();
	glutPostRedisplay();
}

void reshape(int w, int h)		//изменения размеров окна
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv)
{
	srand(static_cast <unsigned> (time(NULL)));		//запускаем таймер
	glutInit(&argc, argv);		//инициализация окна
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Mini golf scene");
	glutFullScreen();
	init();				//инициализация проекта
	glutDisplayFunc(display);	
	glutReshapeFunc(reshape);
	glutIdleFunc(spinDisplay);		//функция простаивания программы
	glutKeyboardFunc(glut_key_action);
	glutMainLoop();
	return 0;
}
void glut_key_action(unsigned char key, int x, int y)		//обработка клавиш

{
	switch (key)
	{
	case 'q':			//выход
		exit(0);
		break;
	case 'a':			//вращение сцены вправо
		angle += .025;
		break;
	case 'd':			//вращение сцены влево
		angle -= .025;
		break;
	case 's':			//остановка вращения
		angle = 0;
		break;
	case 'w':			// вращение мельницы
	{
		if (windmillOn) windmillOn = false;
		else windmillOn = true;
	}
		break;
	case 'b':			// создание мяча
		ballOn = true;
		break;
	case 'k':			// движение мяча назад
			shootOn = true;
			tx += 0.05;
		break;
	case 'i':			// движение мяча вперед
			shootOn = true;
			tx -= 0.05;
		break;
	case 'l':			// движение мяча вправо
			shootOn = true;
			ty += 0.05;
		break;
	case 'j':			// движение мяча влево
			shootOn = true;
			ty -= 0.05;
		break;
	case 'm':			// вращение снеговика
	{
		if (snowmanOn) snowmanOn = false;
		else snowmanOn = true;
	}
		break;
	case 27: //выход из програмы     
		exit(0);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

//рисуем лунку
void drawCircle(float x, float y, float radius)
{
	int i;
	int triangleAmount = 20; //количество треугольников для отрисовки лунки


	   //радиус
	float twicePi = 2.0f * M_PI;
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // центр лунки
	for (i = 0; i <= triangleAmount; i++)
	{
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount)));

	}
	glEnd();

}

static void drawBox(GLfloat size, GLenum type, GLuint text)
{
	static GLfloat n[6][3] =
	{
	  {-1.0, 0.0, 0.0},
	  {0.0, 1.0, 0.0},
	  {1.0, 0.0, 0.0},
	  {0.0, -1.0, 0.0},
	  {0.0, 0.0, 1.0},
	  {0.0, 0.0, -1.0}
	};
	static GLint faces[6][4] =
	{
	  {0, 1, 2, 3},
	  {3, 2, 6, 7},
	  {7, 6, 5, 4},
	  {4, 5, 1, 0},
	  {5, 6, 2, 1},
	  {7, 4, 0, 3}
	};
	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

	glBindTexture(GL_TEXTURE_2D, text);

	for (i = 5; i >= 0; i--) {
		glBegin(type);
		glNormal3fv(&n[i][0]);
		glTexCoord2f(0.0, 0.0);
		glVertex3fv(&v[faces[i][0]][0]);
		glTexCoord2f(0.25, 0.0);
		glVertex3fv(&v[faces[i][1]][0]);
		glTexCoord2f(0.25, 0.25);
		glVertex3fv(&v[faces[i][2]][0]);
		glTexCoord2f(0.0, 0.25);
		glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

static void drawSimpleBox(GLfloat size, GLenum type)
{
	static GLfloat n[6][3] =
	{
	  {-1.0, 0.0, 0.0},
	  {0.0, 1.0, 0.0},
	  {1.0, 0.0, 0.0},
	  {0.0, -1.0, 0.0},
	  {0.0, 0.0, 1.0},
	  {0.0, 0.0, -1.0}
	};
	static GLint faces[6][4] =
	{
	  {0, 1, 2, 3},
	  {3, 2, 6, 7},
	  {7, 6, 5, 4},
	  {4, 5, 1, 0},
	  {5, 6, 2, 1},
	  {7, 4, 0, 3}
	};
	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

	for (i = 5; i >= 0; i--) {
		glBegin(type);
		glNormal3fv(&n[i][0]);
		glVertex3fv(&v[faces[i][0]][0]);
		glVertex3fv(&v[faces[i][1]][0]);
		glVertex3fv(&v[faces[i][2]][0]);
		glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

//отрисовка анимации
void spinDisplay(void)
{
	bool spinIt = true, spinSnowman = true;
	if (spinIt)
	{
		spin += .1;

	}
	if (spinSnowman)
	{
		snowSpin += .1;

	}

	glutPostRedisplay();
}

//таймер анимации
void timer(int id)
{
	if (translating)
	{
		if (tx >= -2.75)
		{
			tx -= .0075;
		}
		else if (tx <= -2.75)
		{
			shootOn = false;
			tAnimating = false;
			translating = false;
			ballOn = false;
			tx = 5.5;
		}

	}

	glutPostRedisplay();

}

GLuint LoadTexture(const char* filename)
{
	GLuint texture;
	int width, height;
	unsigned char* data;

	FILE* file;
	fopen_s(&file, filename, "rb");

	if (file == NULL) return 0;
	width = 1024;
	height = 512;
	data = (unsigned char*)malloc(width * height * 3);
	//int size = fseek(file,);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i < width * height; ++i)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);

	return texture;
}