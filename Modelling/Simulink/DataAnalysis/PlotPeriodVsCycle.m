% MATLAB script to calculate and plot the period of a signal vs cycle number

% 1. Define the filename
filename = 'acq0001.csv';

% 2. Read the data
% Your file has 7 lines of metadata, and the 8th line is the column header.
% We skip the first 8 lines to directly read the numeric data.
data = readmatrix(filename, 'NumHeaderLines', 8);

% 3. Extract Time and Signal data
% Column 1 is Time (s), Column 2 is DIO 0. 
% (Change column index if your signal is on a different DIO channel, e.g., 3 for DIO 1)
time = data(:, 1); 
signal = data(:, 2);

% 4. Find the rising edges
% A rising edge (transition from 0 to 1) means the difference between consecutive points is positive.
edge_indices = find(diff(signal) > 0) + 1; 

% Extract the exact times those rising edges occurred
edge_times = time(edge_indices);

% 5. Calculate the periods
% The period is the difference in time between consecutive rising edges
periods = diff(edge_times);

% 6. Generate the cycle numbers for the x-axis
cycle_numbers = 1:length(periods);

% 7. Plot Period vs. Cycle Number
figure;
plot(cycle_numbers, periods, '-o', 'LineWidth', 1.5, 'MarkerSize', 5, 'MarkerFaceColor', 'b');

% Formatting the plot to look nice
title('Signal Period vs. Cycle Number (DIO 0)');
xlabel('Cycle Number');
ylabel('Period (seconds)');
grid on;

% Optionally, print out some statistics to the Command Window
fprintf('Number of complete cycles found: %d\n', length(periods));
fprintf('Average Period: %.3e seconds\n', mean(periods));
fprintf('Average Frequency: %.2f Hz\n', 1/mean(periods));