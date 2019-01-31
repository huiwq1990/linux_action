
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
相关代码
https://github.com/majek/dump/blob/master/epoll/epoll-dup-example.c

### epoll 压力测试

https://www.cnblogs.com/hxdoit/p/3410199.html
https://github.com/fgutica/linux_epoll_server/blob/master/README.md
https://zickshen.github.io/2018/03/19/%E5%AE%8C%E6%88%90%E4%B8%80%E4%B8%AAC%E8%AF%AD%E8%A8%80http%E6%9C%8D%E5%8A%A1%E5%99%A8%E5%8E%8B%E5%8A%9B%E6%B5%8B%E8%AF%95%E5%B7%A5%E5%85%B7%EF%BC%88%E4%B8%89%EF%BC%89/

### epoll 解析
https://medium.com/@copyconstruct/the-method-to-epolls-madness-d9d2d6378642



### golang conn.File()
https://stackoverflow.com/questions/28967701/golang-tcp-socket-cant-close-after-get-file

### socket是否为非阻塞
https://www.zhihu.com/question/23614342

### EAGAIN

阻塞socket也可能出现EAGAIN
https://blog.csdn.net/cleanfield/article/details/41649985