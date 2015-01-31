typedef struct {
  double px, py, pz;
} Torre;

Torre* CriaTorre(double x, double y, double z);
void DestroiTorre(Torre *n);
void DesenhaTorre(Torre *n, int delta, double r);
