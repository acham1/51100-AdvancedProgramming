% this is a script to plot the results generated from the p3.c's mandelbrot
% set

[filename, pathname, ~] = uigetfile('*', 'p3.c output file');
dim = input('Enter DIM size ');
FID = fopen([pathname filename]);
FORMAT = repmat('%d ', 1, dim);
[A, COUNT] = fscanf(FID, FORMAT, [dim, inf]);
imagesc(A');