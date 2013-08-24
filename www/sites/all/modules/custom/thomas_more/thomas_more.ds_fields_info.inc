<?php

/**
 * @file
 * Display Suite fields.
 */

/**
 * Implements hook_ds_fields_info().
 */
function thomas_more_ds_fields_info($entity_type) {
  $fields = array();
  $file = drupal_get_path('module', 'thomas_more') . '/includes/ds.inc';

  $fields['node']['content-type-label'] = array(
    'title' => t('Content type label'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'function' => 'thomas_more_ds_content_type_label',
    'file' => $file,
    'ui_limit' => array(
      'event|teaser', 'event|teaser_first', 'news|teaser', 'news|teaser_first',
      ),
  );

  $fields['node']['content-type'] = array(
    'title' => t('Content type and title'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'function' => 'thomas_more_ds_content_type_and_title',
    'file' => $file,
    'ui_limit' => array(
      '*|search_result',
      ),
  );

  $fields['node']['campus_list'] = array(
    'title' => t('Campus (comma separated)'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'function' => 'thomas_more_ds_campus_list',
    'file' => $file,
    'ui_limit' => array(
      '*|*',
      ),
  );

  $fields['node']['campus_popup_title_1'] = array(
    'title' => t('Campus title tab 1'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'function' => 'thomas_more_ds_campus_popup_title',
    'file' => $file,
    'ui_limit' => array(
      'campus|*',
      ),
  );

  $fields['node']['campus_popup_title_2'] = array(
    'title' => t('Campus title tab 2'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'function' => 'thomas_more_ds_campus_popup_title',
    'file' => $file,
    'ui_limit' => array(
      'campus|*',
      ),
  );

  $fields['node']['campus_popup_title_3'] = array(
    'title' => t('Campus title tab 3'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'function' => 'thomas_more_ds_campus_popup_title',
    'file' => $file,
    'ui_limit' => array(
      'campus|*',
      ),
  );

  $fields['node']['campus_popup_read_more_1'] = array(
    'title' => t('Campus read-more button tab 1'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'function' => 'thomas_more_ds_campus_popup_read_more',
    'file' => $file,
    'ui_limit' => array(
      'campus|*',
      ),
  );

  $fields['node']['campus_popup_read_more_2'] = array(
    'title' => t('Campus read-more button tab 2'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'function' => 'thomas_more_ds_campus_popup_read_more',
    'file' => $file,
    'ui_limit' => array(
      'campus|*',
      ),
  );

  $fields['node']['campus_popup_read_more_3'] = array(
    'title' => t('Campus read-more button tab 3'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'function' => 'thomas_more_ds_campus_popup_read_more',
    'file' => $file,
    'ui_limit' => array(
      'campus|*',
      ),
  );

  $fields['node']['campus_popup_route_from_to_1'] = array(
    'title' => t('Campus route link tab 1'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'function' => 'thomas_more_ds_campus_popup_route_from_to',
    'file' => $file,
    'ui_limit' => array(
      'campus|*',
      ),
  );

  $fields['node']['campus_popup_route_from_to_2'] = array(
    'title' => t('Campus route link tab 2'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'function' => 'thomas_more_ds_campus_popup_route_from_to',
    'file' => $file,
    'ui_limit' => array(
      'campus|*',
      ),
  );

  $fields['node']['campus_popup_route_from_to_3'] = array(
    'title' => t('Campus route link tab 3'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'function' => 'thomas_more_ds_campus_popup_route_from_to',
    'file' => $file,
    'ui_limit' => array(
      'campus|*',
      ),
  );

  $fields['node']['campus_mobility'] = array(
    'title' => t('Campus mobility'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'function' => 'thomas_more_ds_campus_mobility',
    'file' => $file,
    'ui_limit' => array(
      'campus|*',
      ),
  );

  $fields['node']['campus_facilities'] = array(
    'title' => t('Campus facilities'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'function' => 'thomas_more_ds_campus_facilities',
    'file' => $file,
    'ui_limit' => array(
      'campus|*',
      ),
  );

  if (isset($fields[$entity_type])) {
    return array($entity_type => $fields[$entity_type]);
  }
}
