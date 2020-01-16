#pragma once

/////////////////////////////////////////////////
// FRAME FACTORY
/////////////////////////////////////////////////
class FrameFactory
{
public:
    template<class Frame, typename... Args>
    static Frame* Create(Args... args);

private:
    FrameFactory() {}
};

/////////////////////////////////////////////////
// FRAME FACTORY <template> (definition)
/////////////////////////////////////////////////
template<class Frame, typename... Args>
Frame* FrameFactory::Create(Args... args)
{
    if (Frame* frame = new Frame(args...))
    {
        if (frame->m_Window != nullptr)
        {
            return frame;
        }
        delete frame;
    }
    return nullptr;
}