import numpy as np
from scipy import signal
from scipy.fft import fftshift
import matplotlib.pyplot as plt

N = 100000#2000000#100000#00 #290300
data = np.zeros((N, 2))
file = open("dataDump.txt", "r")

for i in range(0, N):
    line = file.readline()
    data[i] = line.split(',')
'''
###
while i < N:
    line = file.readline()
    if line == '':
        break
    data[i] = line.split(',')
    i += 1
###

file.close()

#data = np.array([[47, 41],[61, 38],[55, 48],[20, 74],[30, 79],[37, 52],[35, 39],[47, 46],[46, 57],[55, 60],[60, 48],[67, 21],[70, 13],[58, 29],[66, 43],[69, 40],[67, 32],[61, 38],[61, 38],[55, 38],[52, 57],[42, 62],[23, 61],[40, 60],[37, 52],[27, 42],[38, 31],[30, 45],[30, 45],[46, 22],[32, 31],[41, 22],[48, 25],[58, 35],[70, 29],[39, 65],[58, 45],[67, 21],[50, 49],[43, 41],[38, 36],[63, 51],[40, 60],[24, 50],[53, 41],[50, 38],[53, 24],[51, 16],[46, 28],[46, 57],[55, 54],[57, 11],[50, 43],[60, 43],[56, 21],[46, 57],[60, 43],[64, 35],[60, 43],[67, 26],[53, 35],[44, 49],[69, 40],[72, 21],[64, 35],[53, 41],[44, 55],[66, 48],[69, 45],[52, 57],[60, 43],[53, 41],[69, 40],[75, 34],[64, 35],[55, 32],[47, 52],[47, 52],[55, 38],[58, 41],[44, 49],[42, 46],[46, 62],[39, 65],[35, 50],[37, 57],[52, 57],[40, 38],[20, 69],[47, 52],[67, 21],[50, 43],[37, 47],[46, 57],[61, 26],[47, 46],[36, 68],[46, 22],[43, 41],[53, 30],[45, 33],[27, 36],[41, 22],[69, 40],[60, 14],[32, 31],[50, 43],[56, 27],[51, 22],[59, 19],[48, 36],[44, 31],[43, 41],[65, 19],[68, 16]])


#data = np.array([[52 + -3j],[37 + -11j],[21 + -12j],[9 + -6j],[29 + -9j],[32 + -6j],[7 + 6j],[24 + 1j],[4 + 15j],[4 + 26j],[32 + 0j],[15 + 0j],[7 + -15j],[4 + -6j],[1 + -9j],[4 + 0j],[1 + -15j],[12 + -54j],[20 + -51j],[-2 + -29j],[-2 + -6j],[17 + -37j],[-13 + -13j],[2 + 1j],[12 + -20j],[-7 + -7j],[-13 + 9j],[-15 + -10j],[9 + -17j],[7 + 6j],[-24 + -7j],[-7 + -1j],[1 + -20j],[-1 + -34j],[4 + -17j],[2 + -31j],[-13 + -22j],[-13 + -28j],[-15 + -20j],[0 + 0j],[2 + -8j],[-12 + 0j],[2 + 18j],[-3 + 40j],[-9 + 30j],[2 + 24j]])
#data = data.reshape((len(data[::, 0]), 1 , len(data[0])))

print(data.shape)

###

rng = np.random.default_rng()

fs = 10e3
N = 1e5
amp = 2 * np.sqrt(2)
noise_power = 0.01 * fs / 2
time = np.arange(N) / float(fs)
mod = 500*np.cos(2*np.pi*0.25*time)
carrier = amp * np.sin(2*np.pi*3e3*time + mod)
noise = rng.normal(scale=np.sqrt(noise_power), size=time.shape)
noise *= np.exp(-time/5)
x = carrier# + noise
print("THIS", x.shape)
print(data[::, 0].shape)

####
fs = 400

time = np.arange(N) / float(fs)
I = data[::, 0] * np.cos(2*np.pi*fs*time)#.reshape(len(data[::, 0]), 1)
Q = data[::, 1] * np.sin(2*np.pi*fs*time)#.reshape(len(data[::, 1]), 1)

A = np.sqrt(I**2 + Q**2)
phi = np.arctan(I/Q)

x = I + Q# + S# A * np.cos(phi)
#print(S.shape)

#x = np.concatenate((C, S), axis=1)
#x = x.reshape((C.shape[0], 2))

#print(x[0:10])
#print(x.shape)


f, t, Sxx = signal.spectrogram(x, fs)#, 102200000)#, fs)
plt.pcolormesh(t, f, Sxx, shading='gouraud')
#plt.plot(range(0, len(x)), x)
plt.ylabel('Frequency [Hz]')
plt.xlabel('Time [sec]')
plt.show()
'''


ax = plt.figure().add_subplot(projection='3d')

# Plot a sin curve using the x and y axes.
x = np.linspace(0, 1, 100)
y = np.sin(x * 2 * np.pi) / 2 + 0.5
ax.plot(x, y, zs=0, zdir='z', label='curve in (x, y)')

# Plot scatterplot data (20 2D points per colour) on the x and z axes.
colors = ('r', 'g', 'b', 'k')

# Fixing random state for reproducibility
np.random.seed(19680801)

x = np.random.sample(20 * len(colors))
y = np.random.sample(20 * len(colors))
c_list = []
for c in colors:
    c_list.extend([c] * 20)
# By using zdir='y', the y value of these points is fixed to the zs value 0
# and the (x, y) points are plotted on the x and z axes.
ax.scatter(x, y, zs=0, zdir='y', c=c_list, label='points in (x, z)')

# Make legend, set axes limits and labels
ax.legend()
ax.set_xlim(0, 1)
ax.set_ylim(0, 1)
ax.set_zlim(0, 1)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

# Customize the view angle so it's easier to see that the scatter points lie
# on the plane y=0
ax.view_init(elev=20., azim=-35, roll=0)

plt.show()