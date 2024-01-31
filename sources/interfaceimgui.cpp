#include "GlfwOcctView.h"
#include "interfaceimgui.h"
#include "modelingcascade.h"

#include <string>
#include "GLFW/glfw3.h"
#include "spdlog/include/spdlog/spdlog.h"
#include <filesystem>


#include "imgui/imgui.h"

#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"


void InterfaceCAD::initGui(Handle(GlfwOcctWindow) &objGLFW)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& aIO = ImGui::GetIO();
    // aIO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    //how to get current directory
    std::string path = std::filesystem::current_path().string();
    spdlog::info("current path: {0}", path);
//Window path
#ifdef _WIN32
    std::string s = "build\\sources";
#endif
//Linux path
#ifdef linux
    std::string s = "build/sources";
#endif

    std::string::size_type i = path.find(s);
    if (i != std::string::npos)
        path.erase(i, s.length());
//Window path
#ifdef _WIN32
    path.append("ttf\\Nevrouz_M.ttf");
#endif
//Linux path
#ifdef linux
      path.append("ttf/Nevrouz_M.ttf");
#endif
    //necessary path for the font
    spdlog::info("necessary path for the font: {0}", path);
    //add user font in form
    aIO.Fonts ->AddFontFromFileTTF(path.c_str(), 18, NULL,
                                  aIO.Fonts->GetGlyphRangesCyrillic());

    ImGui_ImplGlfw_InitForOpenGL(objGLFW->getGlfwWindow(), Standard_True);
    ImGui_ImplOpenGL3_Init();

    // Setup Dear ImGui style.
    //ImGui::StyleColorsClassic();
}


void InterfaceCAD:: menuToolBar(Handle(GlfwOcctWindow) &objGLFW)
{
    if(ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("Clearing all in a window"))
            {
                objView->getContext()->RemoveAll(true);
                objView->getContext()->UpdateCurrentViewer();
            }
            if(ImGui::MenuItem("Maximum Size"))
            {
                objView->getView()->FitAll();
                objView->getView()->Redraw();
            }
            if(ImGui::MenuItem("Exit"))
            {
                glfwSetWindowShouldClose(objGLFW->getGlfwWindow(), GL_TRUE);

            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Workshop"))
        {         
            if(ImGui::MenuItem("Lab 1"))
            {
                //Do something
            }
            else if(ImGui::MenuItem("Lab 2"))
            {
                //Do something
            }
            else if(ImGui::MenuItem("Лабораторная работа 3"))
            {
                //Do something
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Samples"))
        {
            if(ImGui::MenuItem("Demo 3D Primitives"))
            {
                if (objModelingCascade->CreateSome3D(objView))
                {
                    spdlog::info("The 3D objects have been successfully created: code 0x{0}", 0);
                }
            }
            if(ImGui::MenuItem("Create a line"))
            {
                if (objModelingCascade->CreateStraightLine(objView))
                {
                    spdlog::info("The straight line have been successfully created: code 0x{0}", 0);
                }
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}


void InterfaceCAD::renderGui(Handle(GlfwOcctWindow) &objGLFW)
{

    ImGuiIO& aIO = ImGui::GetIO();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    menuToolBar(objGLFW);

    //Window #1 -  Hello IMGUI.
    ImGui::Begin("Hello");
    ImGui::Text("Hello ImGui!");
    ImGui::Text("Hello OpenCASCADE!");
    ImGui::Button("OK");
    ImGui::SameLine();
    ImGui::Button("Cancel");
    ImGui::End();


    int width, height;
    glfwGetWindowSize(objGLFW->getGlfwWindow(), &width, &height);

    //Window #2 - render your GUI
    ImGui::Begin("Windows Info");
    ImGui::SetWindowPos(ImVec2(width - 210, 30), ImGuiCond_::ImGuiCond_None);
    ImGui::SetWindowSize(ImVec2(200,200), ImGuiCond_::ImGuiCond_None);
    if (ImGui::Button("emptyButton")) {
    }

    ImGui::Text("Высота конуса");

    if (ImGui::SliderInt("Red", &m_koef, 1, 10))
    {
        objView->getContext()->Remove(aTestCone, Standard_True);
        objModelingCascade->CreateConus(objView, m_koef, aTestCone);
        objView->getContext()->Display (aTestCone, AIS_Shaded, 0, false);
        objView->getContext()->UpdateCurrentViewer();

    }
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(objGLFW->getGlfwWindow());
}

InterfaceCAD::InterfaceCAD(GlfwOcctView *obj):objView(obj)
{
    objModelingCascade = std::make_unique<ModelingCascade>();
}

InterfaceCAD::~InterfaceCAD()
{

}

void InterfaceCAD::clearImGUI()
{
    // Cleanup IMGUI.
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
