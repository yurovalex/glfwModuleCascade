#pragma once
#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>

class GlfwOcctView;
class ModelingCascade
{
public:
    ModelingCascade();
    ModelingCascade(const ModelingCascade&) = default;
    ModelingCascade(ModelingCascade&&) = default;
    ModelingCascade& operator = (const ModelingCascade&) = default;
    ModelingCascade& operator = (ModelingCascade&&) = default;
    virtual ~ModelingCascade() = default;

    bool CreateConus(GlfwOcctView *obj, int &koef, Handle(AIS_Shape) &aCone);
    bool CreateSome3D(GlfwOcctView *obj) noexcept;
    bool CreateStraightLine(GlfwOcctView *obj) noexcept;

private:
   // GlfwOcctView *objGlfwOcctView;
};


