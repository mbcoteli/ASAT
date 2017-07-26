% HEALPix projection sample

clear

n = 16;      % grid resolution
n_x = 64;  % number of pixel on plane along the axis x
n_y = 48;  % number of pixel on plane along the axis y

SAMPLING = HealpixGenerateSampling(n, 'scoord');

ns = size(SAMPLING, 1);

A = load('C:\Spatial_audio\ASAT\build-MicrophoneArray-Desktop-Debug\3072.txt');
% A = zeros(ns, 1);
% for t = 1:ns
%     A(t) = DebugFunc(SAMPLING(t, 1), SAMPLING(t, 2));
% end

IMG = HealpixPlaneProjBmp(n, A, n_x, n_y);

axes1 = subplot(1, 1, 1);
set(axes1,...
  'XTick',[0:360] * (n_x / 4),...
  'XTickLabel',{'-180','-90','0','90','180'},...
  'YTick',[0:180] * (n_y / 4),...
  'YTickLabel',{'-180','-90','0','90','180'});
%axis(axes1,[0 180 0 180]);


for i=1:n_x
    for j = 1:n_y
        if(IMG(i,j)>0.5)
            Show(i,j) = 255;
        else
            Show(i,j) = 0;
        end
    end
end
imshow(Show);
image('CData', IMG.', 'CDataMapping', 'scaled', 'Parent', axes1);
caxis('auto')
colorbar
axis image
figure


        

BW = im2bw(IMG.', 0.05);


%// Perform connected components analysis
labels = bwlabel(BW);

%// Find the total number of objects in the image
num_labels = max(labels(:));

%// Find centroids of each object and show the image
%imshow(BW);
hold on;

for idx = 1 : num_labels
    %// Find the ith object mask
    mask = labels == idx;

    %// Find the area
    arr = sum(mask(:));

    %// If area is less than a threshold
    %// don't process this object

    %// Else, find the centroid normally
    %// Find non-zero locations
    [rows,cols] = find(mask);

    %// Find the centroid
    
    mean_row(idx) = mean(rows);
    mean_col(idx) = mean(cols);
    
    iy = mean_row(idx);
    ix = mean_col(idx);
    
    y = pi * (iy - 1) / n_y - pi / 2;
    x = 2 * pi * (ix - 1) / n_x;
    
    [ox, oy] = HealpixPlanePoleDistort(x, y);
        if ox < 0
            % out of domain
            continue
        end
        % get projection coordinate on the plane
        [i, j] = HealpixProjectionOntoPlane(n, ox, oy);

    [el(idx),az(idx)]  = HealpixGetSphCoord(16,i,j);
    
    el(idx)= 180 *(el(idx)/pi); 
    az(idx)= 180 *(az(idx)/pi);
    
    
    %// Show the image and the centroid
    plot(mean_col*16, mean_row*16, 'r.', 'MarkerSize', 18);
end
imshow(Show);
imwrite(Show,'3072.png');
