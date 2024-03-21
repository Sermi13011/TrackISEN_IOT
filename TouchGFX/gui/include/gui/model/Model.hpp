#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
    void screenUpdate(char temp[10],char hum[10]);

protected:
    ModelListener* modelListener;
};

#endif // MODEL_HPP
