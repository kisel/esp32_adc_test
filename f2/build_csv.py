import os
import re


kv_by_voltage = {}

for fn in os.listdir("."):
    if re.match("^\d+$", fn) == None:
        continue
    with open(fn) as f:
        print(fn)
        for ln in f.readlines():
            ln = ln.strip()
            parts = re.split("\s+", ln)[1:]
            kv = {}
            print(kv)
            print(parts)
            for i in range(0, len(parts), 2):
                kv[parts[i][:-1]] = int(parts[i+1])
            kv_by_voltage[int(fn)] = kv
            #print(re.split("\s+", ln))
            print(kv)
    #print(fn)

#print(kv_by_voltage)

with open('adc.csv', 'w') as f:
    voltages = sorted(kv_by_voltage.keys())
    f.write('voltage,att0_avg64,att1_avg64,att2_avg64,att3_avg64\n')
    for v in voltages:
        kv = kv_by_voltage[v]
        cols = [v, kv['att0_avg64'],kv['att1_avg64'],kv['att2_avg64'],kv['att3_avg64']]
        f.write(','.join([str(val) for val in cols]) + '\n')

#kv[]

