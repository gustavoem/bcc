typedef struct {
  double px, py, pz;
  double ox, oy, oz;
  double vx, vy, vz;
  /* Outras componentes para o jogo.... */
} Nave;

Nave* CriaNave(double x, double y, double z);

void DestroiNave(Nave *n);

Nave* MoveNave(Nave *n, double ts);
void DesenhaNave(Nave *n, GLfloat a, GLint barrel);
