"""
ラプラス方程式: 数値解法, ヤコビ(Jacobi)法:
12 Aug. 2017
"""
# %matplotlib nbagg
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import ArtistAnimation # アニメーション作成のためのメソッドをインポート

fig = plt.figure()
anim = []

#
delta_L=0.1  # グリッド幅
LL = 10 # 正方形の幅
L = int(LL/delta_L)

V = 5.0 # 1辺の境界の電位
convegence_criterion = 10**-3  # 収束条件。 精度を上げるならこの値を小さくする。

phi = np.zeros([L+1,L+1])
phi[0,:] = V # 境界条件
phi2 = np.empty ([L+1,L+1])

#for plot
im=plt.imshow(phi,cmap='hsv')
anim.append([im])


# メイン
delta = 1.0
n_iter=0
conv_check=[]
while delta > convegence_criterion:
    if n_iter % 100 ==0:  # 収束状況のモニタリング
        print("iteration No =", n_iter, "delta=",delta)
    conv_check.append([n_iter, delta])
    for i in range(L+1):
        for j in range(L+1):
            if i ==0 or i ==L or j==0 or j==L:
                phi2[i,j] = phi[i,j]
            else:
                phi2[i,j] = (phi[i+1,j] + phi[i-1,j] + phi[i,j+1] + phi[i,j-1])/4 # 補遺:式(11)を参照
    delta = np.max(abs(phi-phi2))

    phi, phi2 = phi2, phi
    n_iter+=1

    im=plt.imshow(phi,cmap='hsv')
    anim.append([im])

#for plot
plt.colorbar () # カラーバーの表示
plt.xlabel('X')
plt.ylabel('Y')
ani = ArtistAnimation(fig, anim, interval=100, blit=True,repeat_delay=1000)
ani.save("t.gif", writer='imagemagick')
plt.show()
