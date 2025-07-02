import re
import matplotlib.pyplot as plt

# Read the data from test.out
with open("build/test.out", "r") as f:
    raw_data = f.read()

# Regular expression to extract data
pattern = r"<(p_tree|p_block) \{threads: (\d+)\}>: execution took ([\de\+\.]+) microseconds"
matches = re.findall(pattern, raw_data)

pattern = r"<(serial_linear|seq_tree)>: execution took ([\de\+\.]+) microseconds"
seq_matches = re.findall(pattern, raw_data)

# Separate into dictionaries for each type
tree_data = {}
block_data = {}
serial = 0
sequential = 0

for entry_type, thread_count, time_ns in matches:
    thread_count = int(thread_count)
    time_ns = float(time_ns)
    if entry_type == "p_tree":
        tree_data[thread_count] = time_ns
    else:
        block_data[thread_count] = time_ns

for entry_type, time_ns in seq_matches:
    time_ns = float(time_ns)
    if entry_type == "serial_linear":
        serial = time_ns
    else:
        sequential = time_ns

# Sort by thread count
thread_counts = sorted(set(tree_data.keys()) | set(block_data.keys()))
tree_times = [tree_data.get(t, None) for t in thread_counts]
block_times = [block_data.get(t, None) for t in thread_counts]

# Plotting
plt.figure(figsize=(10, 6))
plt.plot(thread_counts, tree_times, label='p_tree', marker='o')
plt.plot(thread_counts, block_times, label='p_block', marker='s')
plt.plot(thread_counts, [serial for t in thread_counts], label='serial_linear')
plt.plot(thread_counts, [sequential for t in thread_counts], label='seq_tree')
plt.xlabel('Number of Threads')
plt.ylabel('Execution Time (nanoseconds)')
plt.title('Execution Time vs Number of Threads')
plt.legend(loc='center left', bbox_to_anchor=(1, 0.5))
plt.grid(True)

plt.tight_layout()
plt.show()
