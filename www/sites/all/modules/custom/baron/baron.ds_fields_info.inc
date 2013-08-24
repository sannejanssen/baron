<?php

/**
 * @file
 * Display Suite fields.
 */

/**
 * Implements hook_ds_fields_info().
 */
function baron_ds_fields_info($entity_type) {
  $fields = array();
  $file = drupal_get_path('module', 'baron') . '/includes/ds.inc';

  $fields['node']['event_date'] = array(
    'title' => t('Custom event date'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'function' => 'baron_ds_event_date',
    'file' => $file,
    'ui_limit' => array(
      'event|*',
      ),
  );

  if (isset($fields[$entity_type])) {
    return array($entity_type => $fields[$entity_type]);
  }
}
