function [I, Q] = generate_IQ(clk)
    % persistent variables hold state between clock cycles
    persistent state;
    if isempty(state)
        state = 0;
    end

    persistent last_clk;
    if isempty(last_clk)
        last_clk = 0;
    end

    % Detect rising edge
    if (clk == 1 && last_clk == 0)
        state = mod(state + 1, 4);
    end
    last_clk = clk;

    % Map state to I/Q boolean outputs
    switch state
        case 0 % 0 degrees
            I = true;  Q = false;
        case 1 % 90 degrees
            I = true;  Q = true;
        case 2 % 180 degrees
            I = false; Q = true;
        case 3 % 270 degrees
            I = false; Q = false;
        otherwise
            I = false; Q = false;
    end
end