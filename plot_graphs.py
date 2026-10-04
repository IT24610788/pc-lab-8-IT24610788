import matplotlib.pyplot as plt

# Processor counts
cores = [1, 2, 4, 8]

# Recorded execution times (seconds)
times_ex2 = [0.031927, 0.014360, 0.007014, 0.006160]
times_ex3 = [0.376900, 0.195646, 0.121773, 0.099009]

# Calculate Speedup: S = T_1 / T_p
speedup_ex2 = [times_ex2[0] / t for t in times_ex2]
speedup_ex3 = [times_ex3[0] / t for t in times_ex3]

# -------------------------------------------------------------
# Graph 1: Time vs Number of Processors
# -------------------------------------------------------------
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(13, 5))

# Ex 2
ax1.plot(cores, times_ex2, marker='o', color='#1f77b4', linewidth=2, label='Ex 2 (Sum 1..10M)')
ax1.set_title('Exercise 2: Time vs Processors')
ax1.set_xlabel('Number of Processors')
ax1.set_ylabel('Execution Time (seconds)')
ax1.set_xticks(cores)
ax1.grid(True, linestyle='--', alpha=0.6)
ax1.legend()

# Ex 3
ax2.plot(cores, times_ex3, marker='s', color='#ff7f0e', linewidth=2, label='Ex 3 (Monte Carlo Pi)')
ax2.set_title('Exercise 3: Time vs Processors')
ax2.set_xlabel('Number of Processors')
ax2.set_ylabel('Execution Time (seconds)')
ax2.set_xticks(cores)
ax2.grid(True, linestyle='--', alpha=0.6)
ax2.legend()

plt.tight_layout()
plt.savefig('time_vs_processors.png', dpi=300)
plt.close()

# -------------------------------------------------------------
# Graph 2: Speedup vs Number of Processors
# -------------------------------------------------------------
plt.figure(figsize=(8, 5))

# Plot Ex 2, Ex 3, and Ideal Linear Speedup
plt.plot(cores, speedup_ex2, marker='o', color='#1f77b4', linewidth=2, label='Ex 2 Speedup')
plt.plot(cores, speedup_ex3, marker='s', color='#ff7f0e', linewidth=2, label='Ex 3 Speedup')
plt.plot(cores, cores, '--', color='#7f7f7f', label='Ideal Linear Speedup')

plt.title('Speedup vs Number of Processors')
plt.xlabel('Number of Processors')
plt.ylabel('Speedup (T1 / Tp)')
plt.xticks(cores)
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend()

plt.tight_layout()
plt.savefig('speedup_vs_processors.png', dpi=300)
plt.close()

print("Graphs successfully generated and saved:")
print(" - time_vs_processors.png")
print(" - speedup_vs_processors.png")