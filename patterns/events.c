#include <assert.h>
#include <stdio.h>

#define EVENT_MAX_SUBSCRIBER_COUNT 5

typedef void (*event_callback)(void *);

typedef struct {
  size_t count;
  struct {
    void *data;
    event_callback callback;
  } subscribers[EVENT_MAX_SUBSCRIBER_COUNT];
} EventSubscriberPool;

typedef enum {
  EVENT_TYPE_SOMETHING,
  EVENT_TYPE_ELSE,
  EVENT_TYPE_COUNT,
} EventType;

EventSubscriberPool event_subscriber_pool[EVENT_TYPE_COUNT];

void event_subscribe(EventType type, event_callback callback, void *data) {
  assert(event_subscriber_pool[type].count < EVENT_MAX_SUBSCRIBER_COUNT);
  size_t index = event_subscriber_pool[type].count++;
  event_subscriber_pool[type].subscribers[index].callback = callback;
  event_subscriber_pool[type].subscribers[index].data = data;
}

void event_dispatch(EventType type) {
  assert(type < EVENT_TYPE_COUNT);
  for (size_t i = 0; i < event_subscriber_pool[type].count; ++i) {
    void *data = event_subscriber_pool[type].subscribers[i].data;
    event_subscriber_pool[type].subscribers[i].callback(data);
  }
}

void foo(void *data) {
  (void)data;
  printf("foo\n");
}

void bar(const int *b) { printf("bar(%d)\n", *b); }

int main(void) {
  event_subscribe(EVENT_TYPE_SOMETHING, foo, NULL);
  static int a = 2;
  event_subscribe(EVENT_TYPE_SOMETHING, (event_callback)bar, &a);

  printf("Dispatching events\n");
  event_dispatch(EVENT_TYPE_SOMETHING);
}
