# openvpn-xor
openvpn xor 混淆

### 已经打好了补丁,可以直接编译,无需额外再打补丁, 补丁已经在代码内,可以直接查看.其他配置参数跟普通的一样
### 服务器端配置文件需要增加一个字段 xor 如下
```
xor-secret abcdefg
```
### 客户端同样需要增加,两端必须要匹配
```
xor-secret abcdefg
```
### 已知问题
1. 不支持udp模式,udp模式下,混淆无效
