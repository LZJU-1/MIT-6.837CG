#include <GL/glut.h>


void display(void)

{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);

    glVertex2f(0, 0);

    glVertex2f(1.0f, 1.0f);

    glEnd();
    glFlush();
}

int main(int argc,char *argv[])

{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutInitWindowSize(300,300);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OpenGL Window");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}