<?php

/**
 * @file
 * Display Suite functions.
 */

/**
 * DS field: show the content type.
 */
function thomas_more_ds_content_type_label($field) {

  if ($field['entity']->type == 'event' && !empty($field['entity']->field_event_type)) {
    $event_type_id = field_get_items('node', $field['entity'], 'field_event_type');
    $event_type = taxonomy_term_load($event_type_id[0]['tid']);
    return t(ucfirst($event_type->name));
  }
  else {
    $press = field_get_items('node', $field['entity'], 'field_press');
    if ($press && $press[0]['value'] ==  1) {
      // The message is a press message.
      return t('Press');
    }
    else {
      // The message is a news message.
      return t('News');
    }
  }
}

/**
 * DS field: return all campusses separated by comma's.
 */
function thomas_more_ds_campus_list($field) {
  $campus_entities = field_get_items('node', $field['entity'], 'field_campus');
  if (!empty($campus_entities)) {
    $campus_list = array();
    foreach ($campus_entities as $campus_entity) {
      $campus = node_load($campus_entity['target_id']);
      $campus_list[] = $campus->title;
    }
    return implode(', ', $campus_list);
  }
}

/**
 * DS field: show the content type.
 */
function thomas_more_ds_content_type_and_title($field) {
  return '<h2>'. t(ucfirst($field['entity']->type)) . ': ' . $field['entity']->title . '</h2>';
}

/**
 * DS field: return the title of a campus.
 */
function thomas_more_ds_campus_popup_title($field) {
  return '<h3>Campus ' . $field['entity']->title . '</h3>';
}

/**
 * DS field: return a link to the courses on a campus.
 */
function thomas_more_ds_campus_popup_read_more($field) {
  $nid = $field['entity']->nid;
  $title = $field['entity']->title;

  return l('Bekijk de opleidingen aan campus ' . $title, 'node/' . $nid, array('attributes' => array('class' => array('btn'))));
}

/**
 * DS field: return a link to gmail route.
 */
function thomas_more_ds_campus_popup_route_from_to($field) {
  $address = field_get_items('node', $field['entity'], 'field_adress');
  $output = '<div class="route">';
  $output .= 'Bereken route: ';
  $output .= l('Naar hier', 'https://maps.google.be/maps?daddr=' . drupal_encode_path($address[0]['safe_value']));
  $output .= ' of ';
  $output .= l('Van hier', 'https://maps.google.be/maps?saddr=' . drupal_encode_path($address[0]['safe_value']));
  $output .= '</div>';
  return $output;
}

/**
 * DS field: return the campus mobility.
 */
function thomas_more_ds_campus_mobility($field) {
  $node = $field['entity'];

  $field_bus = field_get_items('node', $node, 'field_bus_stop');
  $field_train = field_get_items('node', $node, 'field_train_stop');
  $field_car = field_get_items('node', $node, 'field_car');
  $field_bike = field_get_items('node', $node, 'field_bike');
  $content = '';

  if(!empty($field_bus)) {
    $content .= '<span class="mobility bus"><div class="icon">'. t('Bus') .'</div>'. $field_bus[0]['safe_value'] . '</span>';
  }

  if(!empty($field_train)) {
    $content .= '<span class="mobility train"><div class="icon">'. t('Train') .'</div>'. $field_train[0]['safe_value'] . '</span>';
  }

  if(!empty($field_car)) {
    $content .= '<span class="mobility car"><div class="icon">'. t('Car') .'</div>'. $field_car[0]['safe_value'] . '</span>';
  }

  if(!empty($field_bike)) {
    $content .= '<span class="mobility bike"><div class="icon">'. t('Bike') .'</div>'. $field_bike[0]['safe_value'] . '</span>';
  }

  if ($content != '') {
    $content = '<span class="label-inline label line">' . t('Mobility') . '</span>' . $content;
  }
  return $content;
}


function thomas_more_ds_campus_facilities($field) {
  $nid = $field['entity']->nid;

  $query = new EntityFieldQueryExtraFields();
    $all_facilities = $query->entityCondition('entity_type', 'node')
      ->propertyCondition('type', 'facility')
      ->propertyCondition('status', 1)
      ->addExtraField('field_facility_campus', 'target_id', 'nid')
      ->addExtraField('field_facility_type', 'tid', 'tid')
      ->addExtraField('', 'title', 'title', 'node')
      ->fieldCondition('field_facility_campus', 'target_id', $nid, '=')
      ->execute();

  if (!empty($all_facilities)) {
    $content = '<div class="facility-box">';
    $content .= '<span class="label">'. t('Facilities') .'</span>';
    $content .= '<ul>';

    // Loop through all the facilities for this campus.
    foreach ($all_facilities['node'] as $facility_nid => $facility_info) {
      $term = taxonomy_term_load($facility_info->extraFields->field_facility_type_tid);
      $image = field_get_items('taxonomy_term', $term, 'field_small_icon');
      $content .= '<li class="facility">';
      $content .= theme('image',array('path' => $image[0]['uri'], 'alt' => ''));
      $content .= $facility_info->extraFields->title;
      $content .= '</li>';
    }

    $content .= '</ul>';
    $content .= '</div>';
  }
  return $content;

}

