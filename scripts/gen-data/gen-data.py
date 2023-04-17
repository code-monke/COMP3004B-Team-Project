import math
import random

LOW_COH = "low_coherence"
MED_COH = "med_coherence"
HIGH_COH = "high_coherence"


config = {
    # Number of points
    "max_time": 200, #seconds
    
    # Heart rates
    "min_hr": 60, #bpm
    "max_hr": 100, #bpm
    
    # Coherence levels (ranges)
    # orignal ranges: 
       # [low]0.5 - 1.8, [med]1.8 - 4.0, [high]4.0-16     
       # added overlap to have variations in coherence levels during a session
    HIGH_COH: {
        "min": 0.5,
        "max": 16,
        "mod": 5
    },
    MED_COH: {
        "min": 1.0,
        "max": 5.0,
        "mod": 10
    },
    LOW_COH: {
        "min": 0.5,
        "max": 2.5,
        "mod": 20
    }
}

def array_to_string(arr):
    res = "{"
    for i in range(len(arr)):
        num_str = str(arr[i])
        if i % 10 == 0: res += "\n\t"
        if i % 10 != 0: res += " "
        res += f"{num_str}"
        if i != len(arr) - 1: res += ","
    res += "\n},"
    return res

# Generates a heart rate from sin(t) where t is the current time
# The returned value falls perfectly on sin(t)
def gen_sin_hr(t):
    half_rand_range = (config["max_hr"] - config["min_hr"]) // 2
    return round(math.sin(t / 10) * half_rand_range + config["min_hr"] + half_rand_range, 2)

# Generates heart rate that deviates from sin(t) my adding a random constant
def gen_hr(t, coherence):
    base = gen_sin_hr(t)
    rand_mod = random.randint(-config[coherence]["mod"], config[coherence]["mod"])
    return round(base + rand_mod, 2)    

# Generate coherence score from heart rate
# Coherence score is dependent on how far the heart rate was from gen_sin(t)
# Not how coherence score is actually calculated but gives a useful value
def gen_cs(t, coherence, hr):
    diff_percent = abs(gen_sin_hr(t) - hr) / config[coherence]["mod"]
    cs = config[coherence]["min"] + diff_percent * (config[coherence]["max"] - config[coherence]["min"])
    return round(cs, 2)

# Generates the heart rates and coherence scores over config["max_time"] duration
def gen_data(coherence):
    heart_rates = []
    coh_scores = []
    coh_scores_tmp = []
    for t in range(config["max_time"] + 1):
        if t < config["max_time"]:
            # Generate heart rate
            hr = gen_hr(t, coherence)
            heart_rates.append(hr)

        # Genearate coherence score
        cs = gen_cs(t, coherence, hr)
        coh_scores_tmp.append(cs)
        if t % 5 == 0 and t != 0:
            coh_avg = round(sum(coh_scores_tmp) / len(coh_scores_tmp), 2)
            coh_scores.append(coh_avg)
            coh_scores_tmp = []
        
    return (heart_rates, coh_scores)


if __name__ == "__main__":
    print("Coherence level?")
    print("(1) - HIGH\n(2) - MED\n(3) - LOW")
    choice = int(input())
    out_file = "data-high.txt"
    coherence = HIGH_COH
    if choice == 2: 
        coherence = MED_COH
        out_file = "data-med.txt"
    elif choice == 3: 
        coherence = LOW_COH
        out_file = "data-low.txt"

    with open(out_file, "w") as file:
        heart_rates, coh_scores = gen_data(coherence)
        hr_str = array_to_string(heart_rates)
        cs_str = array_to_string(coh_scores)
        file.write(f"{hr_str}\n{cs_str}")
