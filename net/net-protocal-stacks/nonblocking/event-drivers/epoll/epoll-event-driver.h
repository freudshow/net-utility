/**
 * This work copyright Chao Sun(qq:296449610) and licensed under
 * a Creative Commons Attribution 3.0 Unported License(https://creativecommons.org/licenses/by/3.0/).
 */

#ifndef NET_CORE_EPOLL_EVENT_DRIVER_H
#define NET_CORE_EPOLL_EVENT_DRIVER_H

#include "../ievent-driver.h"

namespace net {
class EpollEventDriver : public IEventDriver {
public:
    /**
     * nevent在kernel 2.6.8之后是被忽略的，参考man 2 epoll_create
     * @param max_events
     * @return
     */
    virtual int init(int max_events) override;
    virtual int add_event(int fd, int cur_mask, int mask) override;
    virtual int del_event(int fd, int cur_mask, int del_mask) override;
    /**
     * 获取epoll的事件。
     * @param events 出参，大小至少为init传入的max_events。
     * @param tp 阻塞等待的时间，若为nullptr为阻塞调用(epoll_wait(..., -1))。
     * @return 获取到的事件个数。
     */
    virtual int event_wait(std::vector<NetEvent> &events, struct timeval *tp) override;

private:
    int m_epfd;
    int m_max_events;
    struct epoll_event *m_events;
};
}

#endif //NET_CORE_EPOLL_EVENT_DRIVER_H