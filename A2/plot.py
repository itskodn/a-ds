import matplotlib.pyplot as plt
import numpy as np

fig, axes = plt.subplots(2, 3, figsize=(18, 10))
fig.suptitle('Сравнительный анализ алгоритмов сортировки', fontsize=16, fontweight='bold')

sizes = []; times = []
with open('mergesort_random.txt', 'r') as f:
    for line in f:
        data = line.strip().split()
        sizes.append(int(data[0])); times.append(float(data[1])) 
axes[0,0].plot(sizes, times, 'b-', linewidth=2)
axes[0,0].set_title('Standard Merge Sort\n(случайные массивы)')
axes[0,0].set_xlabel('Размер массива')
axes[0,0].set_ylabel('Время (мкс)') 
axes[0,0].grid(True, alpha=0.3)

sizes = []; times = []
with open('mergesort_reversed.txt', 'r') as f:
    for line in f:
        data = line.strip().split()
        sizes.append(int(data[0])); times.append(float(data[1])) 
axes[0,1].plot(sizes, times, 'r-', linewidth=2)
axes[0,1].set_title('Standard Merge Sort\n(обратные массивы)')
axes[0,1].set_xlabel('Размер массива')
axes[0,1].set_ylabel('Время (мкс)') 
axes[0,1].grid(True, alpha=0.3)

sizes = []; times = []
with open('mergesort_almost_sorted.txt', 'r') as f:
    for line in f:
        data = line.strip().split()
        sizes.append(int(data[0])); times.append(float(data[1])) 
axes[0,2].plot(sizes, times, 'g-', linewidth=2)
axes[0,2].set_title('Standard Merge Sort\n(почти отсортированные)')
axes[0,2].set_xlabel('Размер массива')
axes[0,2].set_ylabel('Время (мкс)')  
axes[0,2].grid(True, alpha=0.3)

sizes = []; t5=[]; t10=[]; t15=[]; t20=[]; t30=[]; t50=[]
with open('merge&insertion_random.txt', 'r') as f:
    for line in f:
        data = line.strip().split()
        sizes.append(int(data[0]))
        t5.append(float(data[1])); t10.append(float(data[2])) 
        t15.append(float(data[3])); t20.append(float(data[4]))
        t30.append(float(data[5])); t50.append(float(data[6]))
axes[1,0].plot(sizes, t5, label='base=5'); axes[1,0].plot(sizes, t10, label='base=10')
axes[1,0].plot(sizes, t15, label='base=15'); axes[1,0].plot(sizes, t20, label='base=20')
axes[1,0].plot(sizes, t30, label='base=30'); axes[1,0].plot(sizes, t50, label='base=50')
axes[1,0].set_title('Гибридная сортировка\n(случайные массивы)')
axes[1,0].set_xlabel('Размер массива')
axes[1,0].set_ylabel('Время (мкс)')  
axes[1,0].legend(); axes[1,0].grid(True, alpha=0.3)

sizes = []; t5=[]; t10=[]; t15=[]; t20=[]; t30=[]; t50=[]
with open('merge&insertion_reversed.txt', 'r') as f:
    for line in f:
        data = line.strip().split()
        sizes.append(int(data[0]))
        t5.append(float(data[1])); t10.append(float(data[2])) 
        t15.append(float(data[3])); t20.append(float(data[4]))
        t30.append(float(data[5])); t50.append(float(data[6]))
axes[1,1].plot(sizes, t5, label='base=5'); axes[1,1].plot(sizes, t10, label='base=10')
axes[1,1].plot(sizes, t15, label='base=15'); axes[1,1].plot(sizes, t20, label='base=20')
axes[1,1].plot(sizes, t30, label='base=30'); axes[1,1].plot(sizes, t50, label='base=50')
axes[1,1].set_title('Гибридная сортировка\n(обратные массивы)')
axes[1,1].set_xlabel('Размер массива')
axes[1,1].set_ylabel('Время (мкс)') 
axes[1,1].legend(); axes[1,1].grid(True, alpha=0.3)

sizes = []; t5=[]; t10=[]; t15=[]; t20=[]; t30=[]; t50=[]
with open('merge&insertion_almost_sorted.txt', 'r') as f:
    for line in f:
        data = line.strip().split()
        sizes.append(int(data[0]))
        t5.append(float(data[1])); t10.append(float(data[2]))  
        t15.append(float(data[3])); t20.append(float(data[4]))
        t30.append(float(data[5])); t50.append(float(data[6]))
axes[1,2].plot(sizes, t5, label='base=5'); axes[1,2].plot(sizes, t10, label='base=10')
axes[1,2].plot(sizes, t15, label='base=15'); axes[1,2].plot(sizes, t20, label='base=20')
axes[1,2].plot(sizes, t30, label='base=30'); axes[1,2].plot(sizes, t50, label='base=50')
axes[1,2].set_title('Гибридная сортировка\n(почти отсортированные)')
axes[1,2].set_xlabel('Размер массива')
axes[1,2].set_ylabel('Время (мкс)') 
axes[1,2].legend(); axes[1,2].grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('comparison_analysis.png', dpi=300, bbox_inches='tight')
plt.show() 