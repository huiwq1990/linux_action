
边缘触发和水平触发的实验
http://www.cnblogs.com/charlesblc/p/5521086.html


oneshot实验
https://www.cnblogs.com/charlesblc/p/5538363.html


两个epoll实例可以监听同一个fd
http://man7.org/linux/man-pages/man7/epoll.7.html

epoll的fd是否可以共享，可以但是不建议这么做
https://stackoverflow.com/questions/31357215/is-it-ok-to-share-the-same-epoll-file-descriptor-among-threads

### epoll设计缺陷及使用指导
水平触发，有惊群问题；边缘触发，有饥饿问题
https://idea.popcount.org/2017-02-20-epoll-is-fundamentally-broken-12/