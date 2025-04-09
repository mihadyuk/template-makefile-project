#ifndef QTEXAMPLESKELETON_H
#define QTEXAMPLESKELETON_H

class QtExampleSkeleton
{
public:
    QtExampleSkeleton();

    QtExampleSkeleton(const QtExampleSkeleton &) = delete;
    QtExampleSkeleton(QtExampleSkeleton &&) = delete;
    QtExampleSkeleton &operator=(const QtExampleSkeleton &) = delete;
    QtExampleSkeleton &operator=(QtExampleSkeleton &&) = delete;

    virtual ~QtExampleSkeleton();

};

#endif // QTEXAMPLESKELETON_H
