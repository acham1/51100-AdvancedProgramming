% this is a script to plot the results generated from the p3.c's mandelbrot
% set

dim = input('Enter DIM size ');

disp('Getting serial output');
[filename, pathname, ~] = uigetfile('*', 'serial p3.c output file');
FID = fopen([pathname filename]);
FORMAT = repmat('%d ', 1, dim);
[A, COUNT] = fscanf(FID, FORMAT, [dim, inf]);
subplot(1,3,1);
imagesc(A');
axis equal;
title('serial');
fclose(FID);

disp('Getting static omp output');
[filename, pathname, ~] = uigetfile('*', 'static omp p3.c output file');
FID = fopen([pathname filename]);
FORMAT = repmat('%d ', 1, dim);
[A, COUNT] = fscanf(FID, FORMAT, [dim, inf]);
subplot(1,3,2);
imagesc(A');
axis equal;
title('static omp');
fclose(FID);

disp('Getting dynamic omp output');
[filename, pathname, ~] = uigetfile('*', 'dynamic omp p3.c output file');
FID = fopen([pathname filename]);
FORMAT = repmat('%d ', 1, dim);
[A, COUNT] = fscanf(FID, FORMAT, [dim, inf]);
subplot(1,3,3);
imagesc(A');
axis equal;
title('dynamic omp');
fclose(FID);

print([pathname 'p3.results_mandelbrot.png'], '-dpng');