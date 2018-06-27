#include "gui/console_frame.h"

#include <string>
#include <stdexcept>

#include <wx/msgdlg.h>

#include "gui/app.h"
#include "gui/dynamical_dialog.h"

#include "gui/solution_dialog.h"

#include "util/util.h"

namespace dynsolver {
namespace gui {

console_frame::console_frame(app& app) : console_frame_base(nullptr, wxID_ANY, "Console"),
					 appl(app), variablesComboBoxValue("") {
  // Add in widgets and setup events not already done in console_frame_base.
  equationsDataViewCtrl->AppendTextColumn("Variable");
  equationsDataViewCtrl->AppendTextColumn("Expression", wxDATAVIEW_CELL_EDITABLE);

  solutionsDataViewCtrl->AppendTextColumn("ID");
  solutionsDataViewCtrl->AppendTextColumn("Increment");
  solutionsDataViewCtrl->AppendTextColumn("T Min");
  solutionsDataViewCtrl->AppendTextColumn("T Max");
  set_no_compile();
  solutionsEditButton->Disable();
  solutionsDeleteButton->Disable();
}

console_frame::~console_frame() { }

void console_frame::lorenz_example_menu_item_on_menu_selection(wxCommandEvent&) {
  variablesComboBox->SetValue("3");
  
  equationsDataViewCtrl->DeleteAllItems();
  wxVector<wxVariant> data;
  data.push_back(wxVariant("x1"));
  data.push_back(wxVariant("10*(x2-x1)"));
  equationsDataViewCtrl->AppendItem(data);
  data.clear();
  data.push_back(wxVariant("x2"));
  data.push_back(wxVariant("x1*(28-x3)-x2"));
  equationsDataViewCtrl->AppendItem(data);
  data.clear();
  data.push_back(wxVariant("x3"));
  data.push_back(wxVariant("x1*x2-x3*8/3"));
  equationsDataViewCtrl->AppendItem(data);
  data.clear();

  compileButton->Enable();
}

void console_frame::new_dynamical_window_menu_item_on_selection(wxCommandEvent&) {
  dynamical_window_specification spec;
  spec.horizontalAxisMin = -5;
  spec.horizontalAxisMax = 5;
  spec.verticalAxisMin = -5;
  spec.verticalAxisMax = 5;
  spec.horizontalAxisVariable = 0;
  spec.verticalAxisVariable = 1;
  spec.dynamicalVariables = appl.get_model().get_dynamical_variables();
  if(appl.get_dynamical_window_dialog()->show_dialog(spec, &spec)) {
    appl.new_dynamical_window(spec);
  }
}

void console_frame::close_dynamical_windows_menu_item_on_selection(wxCommandEvent&) {
  appl.delete_all_dynamical_windows();
}

void console_frame::console_frame_on_close(wxCloseEvent& evt) {
  appl.close_application();
}

void console_frame::set_no_compile() {
  variablesComboBox->SetValue(variablesComboBoxValue);
  compileButton->Disable();
  equationsDataViewCtrl->DeleteAllItems();
  newDynamicalWindowMenuItem->Enable(false);
}

void console_frame::set_yes_compile() {
  newDynamicalWindowMenuItem->Enable(true);
}

void console_frame::compile_button_on_button_click(wxCommandEvent& event) {
  // We first verify that each expression is nonempty
  int variables = equationsDataViewCtrl->GetItemCount();
  if(variables < 1) {
    assert(false);
    return;
  }
  std::vector<std::string> expressions;
  for(int row = 0; row != variables; ++row) {
    std::string value(equationsDataViewCtrl->GetTextValue(row, 1));
    expressions.push_back(value);
    if(value.empty()) {
      wxMessageDialog messageDialog(nullptr, "One of the expressions is empty!",
				    "Error", wxOK);
      messageDialog.ShowModal();
      return;
    }
  }
  if(!appl.compile(expressions)) {
    wxMessageDialog messageDialog(nullptr, "The Compilation Failed!",
				  "Compilation Error", wxOK);
    messageDialog.ShowModal();
  }
}

void console_frame::read_variables_combo_box_input() {
  int variables(0);
  std::string variablesString(variablesComboBox->GetValue().ToStdString());
  if(!util::has_only_digits(variablesString)) {
    variablesComboBox->SetValue(variablesComboBoxValue);
    return;
  }
  try {
    variables = std::stoi(variablesString);
  } catch(const std::invalid_argument& exc) {
    variablesComboBox->SetValue(variablesComboBoxValue);
    return;
  } catch(const std::out_of_range& exc) {
    variablesComboBox->SetValue(variablesComboBoxValue);
    return;
  }

  if(variables <= 0) {
    variablesComboBox->SetValue(variablesComboBoxValue);
    return;
  }
  variablesComboBoxValue = variablesString;
  update_equations_data_view_ctrl(variables);
}

void console_frame::variables_combo_box_on_text_enter(wxCommandEvent& evt) {
  SetFocus(); // Sets the focus to the underlying frame.
  // No need to do anything since the text box loses focus anyway after this
  // event is called.
}

void console_frame::variables_combo_box_on_kill_focus(wxFocusEvent& evt) {
  read_variables_combo_box_input();
}

void console_frame::variables_combo_box_on_combo_box(wxCommandEvent& evt) {
  int variables(std::stoi(variablesComboBox->GetValue().ToStdString()));
  update_equations_data_view_ctrl(variables);
}

void console_frame::update_equations_data_view_ctrl(int variables) {
  assert(variables >= 1);
  if(variables == equationsDataViewCtrl->GetItemCount()) return;
  equationsDataViewCtrl->DeleteAllItems();
  wxVector<wxVariant> data;
  for(int i = 0; i != variables; ++i) {
    data.push_back(wxVariant("x" + std::to_string(i+1)));
    data.push_back(wxVariant(""));
    equationsDataViewCtrl->AppendItem(data);
    data.clear();
  }
  compileButton->Enable();
}

void console_frame::solutions_data_view_ctrl_on_selection_changed(wxDataViewEvent& evt) {
  process_select_row();
}

void console_frame::update_solutions_list() {
  solutionsDataViewCtrl->DeleteAllItems();
  for(std::unordered_map<solution_id, solution>::const_iterator
	iter = appl.get_model().get_solutions().begin();
      iter != appl.get_model().get_solutions().end(); ++iter) {
    wxVector<wxVariant> data;
    data.push_back(wxVariant(std::to_string(iter->first)));
    data.push_back(wxVariant(std::to_string(iter->second.specification.increment)));
    data.push_back(wxVariant(std::to_string(iter->second.specification.tMin)));
    data.push_back(wxVariant(std::to_string(iter->second.specification.tMax)));
    solutionsDataViewCtrl->AppendItem(data);
  }
}

void console_frame::select_solution(solution_id id) {
  wxVariant value;
  for(int i = 0; i != solutionsDataViewCtrl->GetItemCount(); ++i) {
    solutionsDataViewCtrl->GetValue(value, i, 0);
    int rowId = std::stoi(value.GetString().ToStdString());
    if(rowId == id) {
      solutionsDataViewCtrl->SelectRow(i);
      process_select_row();
      return;
    }
  }
  assert(false);
}

void console_frame::process_select_row() {
  if(solutionsDataViewCtrl->GetSelectedRow() != wxNOT_FOUND) {
    color color(1.0, 0.0,0.0,1.0);
    appl.clear_solution_color();
    appl.set_solution_color(get_selected_solution_id(), color);
    solutionsEditButton->Enable();
    solutionsDeleteButton->Enable();
  } else {
    // Unselect
    solutionsEditButton->Disable();
    solutionsDeleteButton->Disable();
    appl.clear_solution_color();
  }
}

void console_frame::unselect_solution() {
  int row = solutionsDataViewCtrl->GetSelectedRow();
  if(row != wxNOT_FOUND) {
    solutionsDataViewCtrl->UnselectRow(row);
    process_select_row();
  }
  
}

void console_frame::solutions_edit_button_on_button_click(wxCommandEvent&) {
  solution_id solutionId(get_selected_solution_id());
  solution_specification spec(appl.get_model().get_solutions().at(solutionId).specification);
  if(appl.get_solution_dialog()->show_dialog(spec, &spec)) {
    appl.edit_solution(solutionId, spec);
  }
}
void console_frame::solutions_delete_button_on_button_click(wxCommandEvent&) {
  appl.delete_solution(get_selected_solution_id());
}

solution_id console_frame::get_selected_solution_id() {
  wxVariant value;
  solutionsDataViewCtrl->GetValue(value, solutionsDataViewCtrl->GetSelectedRow(), 0);
  return std::stoi(value.GetString().ToStdString());
}
void console_frame::singular_points_edit_button_on_button_click(wxCommandEvent&) {
}
void console_frame::singular_points_delete_button_on_button_click(wxCommandEvent&) {
}
} // namespace gui
} // namespace dynsolver
