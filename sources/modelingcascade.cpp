#include "modelingcascade.h"
#include "GlfwOcctView.h"
#include <gp_Ax2.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>


ModelingCascade::ModelingCascade()
{

}

bool ModelingCascade::CreateSome3D(GlfwOcctView *obj) noexcept
{
    obj->getContext()->RemoveAll(true);
    obj->getContext()->UpdateCurrentViewer();
    gp_Ax2 anAxis;
    anAxis.SetLocation (gp_Pnt (0.0, 0.0, 0.0));
    Handle(AIS_Shape) aBox = new AIS_Shape (BRepPrimAPI_MakeBox (anAxis, 50, 50, 50).Shape());
    obj->getContext()->Display (aBox, AIS_Shaded, 0, false);
    anAxis.SetLocation (gp_Pnt (25.0, 125.0, 0.0));

    anAxis.SetLocation (gp_Pnt (100, 100.0, 0.0));
    Handle(AIS_Shape) aCylinder = new AIS_Shape (BRepPrimAPI_MakeCylinder(anAxis, 25, 50, 3 * M_PI/2).Shape());
    obj->getContext()->Display (aCylinder, AIS_Shaded, 0, false);

    anAxis.SetLocation (gp_Pnt (150, 50.0, 0.0));
    Handle(AIS_Shape) aTorus = new AIS_Shape (BRepPrimAPI_MakeTorus(anAxis, 30, 15, 3 * M_PI/2).Shape());
    obj->getContext()->Display (aTorus, AIS_Shaded, 0, false);

    anAxis.SetLocation (gp_Pnt (150, 150.0, 0.0));
    Handle(AIS_Shape) aSphere= new AIS_Shape (BRepPrimAPI_MakeSphere(anAxis, 30, 3 * M_PI/2).Shape());
    obj->getContext()->Display (aSphere, AIS_Shaded, 0, false);
    return true;
}


#include <Geom_Line.hxx>
#include <gp_Pnt.hxx>
#include <gp_Dir.hxx>
#include <gp_Vec.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
bool ModelingCascade::CreateStraightLine(GlfwOcctView *obj) noexcept
{
    // Define the start and end points of the line
    gp_Pnt startPoint(0., 0., 0.);
    gp_Pnt endPoint(1., 1., 0.);

    // Create a direction vector for the line
    gp_Dir direction(gp_Vec(startPoint, endPoint));

    // Create the line using the start point and direction
    Handle(Geom_Line) line = new Geom_Line(startPoint, direction);

    //!Get points the coordinates of some points on the line
    //gp_Pnt point1 = line->Value(0); // Start point
    //gp_Pnt point2 = line->Value(0.5); // Midpoint
    //gp_Pnt point3 = line->Value(1); // End point

    // Create an AIS_Shape object and initialize it with the Geom_Line
    TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(line);
    Handle(AIS_Shape) shape = new AIS_Shape(edge);
    obj->getContext()->Display (shape, AIS_Shaded, 0, true);

   return true;
}

bool ModelingCascade::CreateConus(GlfwOcctView *obj, int &koef , Handle(AIS_Shape) &aCone)
{
    gp_Ax2 anAxis;
    anAxis.SetLocation (gp_Pnt (25.0, 125.0, 0.0));
    aCone = new AIS_Shape (BRepPrimAPI_MakeCone (anAxis, 25, 0, 10*koef).Shape());
    return true;
}
