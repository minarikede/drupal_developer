<?php
/**
 *
 * User: KováCsaba kovacs.csaba@cheppers.com
 * Date: 2012.12.29.
 * To change this template use File | Settings | File Templates.
 */

  /**
   * Foo form.
   */
function endresz_gradebook_set_semester_form($form, &$form_state){
  $form = array();
  $semester_term = taxonomy_vocabulary_machine_name_load('tanev_felev');
  $semester = taxonomy_get_tree($semester_term->vid, $parent = 0, $max_depth = NULL, $load_entities = FALSE);

  $options = array();
  foreach($semester as $value) {
    $options[$value->tid] = $value->name;
  }

  $form['semester'] = array(
    '#type' => 'select',
    '#title' => t('Set active semester'),
    '#options' => $options,
    '#default_value' => variable_get('active_semester_id', 0),
    '#description' => t('Select the default semester and click save'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save')
  );

  return $form;
}

/**
 * Validate callback for Foo form.
 */
function endresz_gradebook_set_semester_form_validate(&$form, &$form_state){
  $semester_term = taxonomy_vocabulary_machine_name_load('tanev_felev');
  $semester = taxonomy_get_tree($semester_term->vid, $parent = 0, $max_depth = NULL, $load_entities = FALSE);
  $semesters = array();
  foreach($semester as $value) {
    $semesters[] = $value->tid;
  }
  if (!in_array($form_state['values']['semester'],$semesters)) {
    form_error($form, t('Invalid semester value'));
  }
}
/**
 * Submit callback for Foo form.
 */
function endresz_gradebook_set_semester_form_submit(&$form, &$form_state){
  variable_set('active_semester_id', $form_state['values']['semester']);
  $term = taxonomy_term_load($form_state['values']['semester']);
  drupal_set_message(t('The %semester has been activated.', array('%semester' => $term->name)));
}


function endresz_gradebook_admin() {
  $items[] = l(t('Administer classes'), 'admin/structure/taxonomy/osztalyok');
  $items[] = l(t('Administer subjects'), 'admin/structure/taxonomy/tantargyak');
  $items[] = l(t('Add semester'), 'admin/structure/taxonomy/tanev_felev');
  $items[] = l(t('Set active semester'), 'admin/gradebook/semester');
  $items[] = l(t('Administer grade types'), 'admin/structure/taxonomy/grade_type');
  $items[] = l(t('Administer message type'), 'admin/structure/taxonomy/message_type');
  
  return theme('item_list', array('items' => $items, 'title' => t('Administer gradebook settings')));
}