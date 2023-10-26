#include <windows.h>  
#include <gl/glut.h>  
#include <math.h>     
#define GL_PI 3.1415f 


static GLfloat xRot = 0.0f; //表示沿x轴的旋转角度
static GLfloat yRot = 0.0f; //表示沿y轴的旋转角度


GLfloat  whiteLight[] = { 0.2f,0.2f,0.2f,1.0f }; //表示白色光源的环境光分量
GLfloat  lightPos[] = { 0.0f,0.0f,0.0f,1.0f };    //表示光源的位置


void Display(void) //定义一个函数，用于渲染场景
{
    static float fMoonRot = 0.0f; //定义一个静态变量，表示月球绕地球的旋转角度
    static float fEarthRot = 0.0f; //定义一个静态变量，表示地球绕太阳的旋转角度
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除颜色缓冲区和深度缓冲区
    glPushMatrix(); //保存当前矩阵
    glTranslatef(0.0f, 0.0f, -400.0f); //将场景沿z轴负方向平移400个单位



    //绘制太阳
    glColor3ub(255, 0, 0); //设置颜色为红色
    glDisable(GL_LIGHTING);   //关闭光源  
    glutSolidSphere(60.0f, 200.0f, 200.0f); //绘制一个半径为60，分段数为200的实心球体
    glEnable(GL_LIGHTING);    //启动光源
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos); //设置光源的位置为lightPos所指定的值



    //绘制地球轨道
    glRotatef(fEarthRot, 0.0f, 1.0f, 0.0f); //将场景沿y轴正方向旋转fEarthRot度
    glColor3ub(255, 0, 0);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidTorus(1.0f, 200.0f, 300.0f, 300.0f); //绘制一个内半径为1，外半径为200，侧面数和环数为300的实心圆环
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    //绘制地球
    glColor3ub(0, 0, 255); //设置颜色为蓝色
    glTranslatef(200.0f, 0.0f, 0.0f); //将场景沿x轴正方向平移200个单位
    glutSolidSphere(15.0f, 50.0f, 50.0f);      //绘制一个半径为15，分段数为50的实心球体  



    //根据基于地球的坐标进行旋转，并绘制月球  
    glColor3ub(255, 255, 0); //设置颜色为黄色
    glRotatef(fMoonRot, 0.0f, 1.0f, 0.0f); //将场景沿y轴正方向旋转fMoonRot度
    glTranslatef(30.0f, 0.0f, 0.0f); //将场景沿x轴正方向平移30个单位
    glutSolidSphere(5.0f, 30.0f, 30.0f);  //绘制一个半径为5，分段数为30的实心球体。


    fMoonRot += 12.0f; //每次增加月球的旋转角度12度
    if (fMoonRot >= 360.0f) fMoonRot = 0.0f; //如果月球的旋转角度超过了360度，则重置为零


    glPopMatrix(); //恢复之前保存的矩阵
    fEarthRot += 1.0f; //每次增加地球的旋转角度1度
    if (fEarthRot >= 360.0f)fEarthRot = 0.0f; //如果地球的旋转角度超过了360度，则重置为零

    glutSwapBuffers(); //交换双缓冲区
}

void ChangeSize(int w, int h) //定义一个函数，用于处理窗口事件
{
    if (h == 0)h = 1;
    GLfloat fAspect; //定义一个变量，表示窗口的宽高比
    glViewport(0, 0, w, h); //设置视口为整个窗口
    fAspect = (GLfloat)w / (GLfloat)h; //计算宽高比
    glMatrixMode(GL_PROJECTION); //切换到投影矩阵模式
    glLoadIdentity(); //加载单位矩阵
    gluPerspective(45.0f, fAspect, 1.0, 1000); //设置透视投影，视角为45度，近裁剪面为1，远裁剪面为1000

    gluLookAt(0.0f, 100.0f, 0.0f, 0.0f, 0.0f, -300.0f, 0.0f, 0.0f, -1.0f); //设置观察点的位置和方向，从(0,100,0)看向(0,0,-300)，上方向为(0,0,-1)

    glMatrixMode(GL_MODELVIEW); //切换到模型视图矩阵模式
    glLoadIdentity(); //加载单位矩阵
}


void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(50, TimerFunc, 1);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 600);
    glutCreateWindow("太阳，地球，月亮动态图");
    glutDisplayFunc(Display);
    glutReshapeFunc(ChangeSize);


    glEnable(GL_DEPTH_TEST); //启用深度测试
    glEnable(GL_COLOR_MATERIAL); //启用颜色材质
    glClearColor(0.0f, 0.0f, 0.15f, 1.0f); //设置背景颜色为深蓝色

    glEnable(GL_LIGHTING);                             //启动光源  
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight); //使用whiteLght所指定的环境光  
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);         //设置光源的位置为lightPos所指定的值  
    glEnable(GL_LIGHT0); //启用第一个光源

    glutTimerFunc(500, TimerFunc, 1); //自动动画，计时器  
    glutMainLoop();
    return 0;
}
