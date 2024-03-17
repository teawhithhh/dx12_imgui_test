#ifndef INPUT_TEXT
#define INPUT_TEXT

#include <string>
#include "imgui.h"
#include "imgui_internal.h"
#include "parser.hxx"
#include "logger.hxx"
#include "widget.hxx"

class InputText : public Widget {
    public:
      InputText(std::string label, const ImVec2 &sizeArg, const float &rounding,
                char *buffer, size_t bufferLen);

      bool operator()() override;

      ~InputText();
    private:
      std::string label_;

      ImVec2 sizeArg_;
      float rounding_;
      ImVec2 textSize_;

      char* buffer_;
      char* bufferEnd_;
      size_t bufferLen_;

      bool isEditing_ = false;
      ImVec2 labelSize_;

      std::string shiftAndDelete(const std::string& str);
};

#endif
