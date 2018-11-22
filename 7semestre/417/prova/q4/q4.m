% To run this code you need to install the image package:
% https://octave.sourceforge.io/image/
pkg load image

% imagem original invertida 
% (acho mais intuitivo selecionar o conteúdo do que o não-conteúdo)
a = imread ('input/4.bmp');
a = imcomplement (a);


% tophat da imagem original
se = strel ('disk', 20, 0);
b = imtophat (a, se);


% abertura para desfazer pequenos pontos brancos que não são texto
se = strel ('disk', 4, 0);
c = imopen (b, se);


% reconstroi a original a partir de c
d = imreconstruct (c, a);


% acha o limiar usando método de otsu e faz o threshold da imagem
t = graythresh (d, 'otsu')
e = im2bw (d, t);


% remove elementos com área pequena
% f idealmente contém apenas as palavras da imagem
f = bwareafilt (e, [200, +inf]);


% Vamos encontrar pedaços das palavras que são possíveis junções de 
% palavras
% 1) primeiro vamos encontrar pedaços da imagem que não tem muitos 
% pixels brancos acima nem abaixo. Para fazer isso, vamos dilatar 
% verticalmente a imagem; é esperado que as letras formem um algomerado 
% maior do que o valor dilatado, enquanto as junções de palavras não. 
% Portanto, possíveis junções devem ser pedaços que, verticalmente, são 
% menores do que o resto da imagem.

% Dilatamos por 50, deve ser suficiente para aglomerar as letras sem
% juntar as linhas
h = imdilate (f, strel ('rectangle', [50, 1]));


% agora vamos fazer um tophat, isso deve nos dar possíveis junções. 
se = strel ('rectangle', [60, 1]);
i = h - imopen (h, se);
i = bwmorph (i, 'dilate', 5);

% 2) agora vamos selecionar pontos da imagem que são linhas horizontais.
% esqueleto morfológico de f
g = bwmorph (f, 'skel', inf);
% traços horizontais
j = imopen (bwmorph (g, 'dilate', 1), strel ('rectangle', [1, 20]));

% k é a intersecção de i e j. Vamos usar k para segmentar a imagem f,
% então primeiro transformamos a imagem em um conjunto de pontos 
% (junções das palavras) e depois dilatamos verticalmente e invertemos
% a imagem.
k = i .* j;
k = bwmorph (bwmorph (k, 'skel', inf) , 'shrink', inf);
k = imdilate (k, strel ('rectangle', [50, 4]));
k = imcomplement (k);


% A imagem final são labels de f segmentada por k
l = k .* f;
[l, x] = bwlabel (l, 4);
l = label2rgb (l);


% Salva todas imagens descritas no processo
imwrite (a, "a.bmp");
imwrite (b, "b.bmp");
imwrite (c, "c.bmp");
imwrite (d, "d.bmp");
imwrite (e, "e.bmp");
imwrite (f, "f.bmp");
imwrite (g, "g.bmp");
imwrite (h, "h.bmp");
imwrite (i, "i.bmp");
imwrite (j, "j.bmp");
imwrite (k, "k.bmp");
imwrite (l, "l.bmp");
