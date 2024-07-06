clc, clearvars, close all;
my_csv = readtable('edited.csv'); 

data = my_csv{:, 5};


window_size = 100;
rms_values = zeros(1, ceil(length(data) / window_size)); 
for i = 1:window_size:length(data)
    rms_values((i + window_size - 1) / window_size) = rms(data(i:min(i + window_size - 1, end)));
end

stem(rms_values);
xlabel('samples');
ylabel('current (rms in A)');
title('Root Mean Square (RMS) Value Plot');
