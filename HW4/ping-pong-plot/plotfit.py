import pandas, numpy
df = pandas.read_excel('ping-pong.xlsx')
print('Keys: ',df.keys(),'\n')
messageSize=df.messageSize
sameNode=df.sameNode
diffNode=df.diffNode
z1 = numpy.polyfit(messageSize, sameNode, 1) #z = np.polyfit(x, y, 3)
print('z1:\n',z1)
z2 = numpy.polyfit(messageSize, diffNode, 1) #z = np.polyfit(x, y, 3)
print('z2:\n',z2)