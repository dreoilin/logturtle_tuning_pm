% LC circuit parameters
L = 5e-6;
CN = 4e-9;
CP = 4e-9;
R = 0.2;
VDD = 10;
        
tcmp = 5;

% resolution of counters
cnt_n_bits = 9;
% delay before gate drive
% sufficiently small to enable pulse generation
cnt_min = 10;

fin = 1e6;
% number of phase cycles to introduce phase keying
N_PHASE_CYCLES = 4;
fL = 2*pi * (fin) / (2*pi + pi/2/N_PHASE_CYCLES);
fH = 2*pi * (fin) / (2*pi - pi/2/N_PHASE_CYCLES);

%

modelName = 'TX_TUNE_DIGITALv5';
in = Simulink.SimulationInput(modelName);

% Run the simulation
out = sim(in);
%%
% Derive on time of excitation signal
X = out.CNT.Data;
D = 0.5 * (X / ( 2^cnt_n_bits) + 1);
fprintf("Duty Cycle: %f\n", D);
