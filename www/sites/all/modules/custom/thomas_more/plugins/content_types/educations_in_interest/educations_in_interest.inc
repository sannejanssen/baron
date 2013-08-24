<?php

/**
 * @file
 * Plugin to handle eductions in interests.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Educations block on interest'),
  'defaults' => array(),
  'category' => t('Thomas More'),
);

/**
 * Output function for the educations in interests block.
 */
function thomas_more_educations_in_interest_content_type_render($subtype, $conf, $panel_args) {

  $content = '';
  $node = menu_get_object();

  if ($node && $node->type == 'area_of_interest') {

    // We load the campuses, and key it on nid.
    $campus_records = array();
    $results = db_query("SELECT nid, title FROM {node} n WHERE n.status = 1 AND n.type = 'campus'");
    foreach ($results as $record) {
      $campus_records[$record->nid] = $record->title;
    }

    // Get the educations. We first get the main ones, then the follow ups.
    foreach (array(MAIN_EDUCATION, FOLLOW_UP_EDUCTION) as $value) {
      $query = new EntityFieldQueryExtraFields();
        $main_courses = $query->entityCondition('entity_type', 'node')
        ->propertyCondition('type', 'education')
        ->propertyCondition('status', 1)
        ->addExtraField('', 'title', 'title', 'node')
        ->addExtraField('field_campus', 'target_id', 'nid')
        ->fieldCondition('field_vervolgopleiding', 'value', $value, '=')
        ->fieldCondition('field_interessegebied', 'target_id', $node->nid)
        ->execute();

        $rows = array();

        if (!empty($main_courses)) {
          foreach ($main_courses['node'] as $nid => $info) {
            $row = array();

            // Title.
            $row[] = array('data' => l(check_plain($info->extraFields->title), 'node/' . $info->nid), 'class' => array('education'));

            // Campus.
            $campus = array();
            if (!empty($info->extraFields->field_campus_nid)) {
              if (is_array($info->extraFields->field_campus_nid)) {
                foreach ($info->extraFields->field_campus_nid as $cid) {
                  if (is_array($cid)) {
                    foreach ($cid as $cid_a) {
                      $campus[] = l($campus_records[$cid_a], 'node/' . $cid_a);
                    }
                  }
                  else {
                    $campus[] = l($campus_records[$cid], 'node/' . $cid);
                  }
                }
              }
              else {
                $campus[] = l($campus_records[$info->extraFields->field_campus_nid], 'node/' . $info->extraFields->field_campus_nid);
              }
            }
            $row[] = array('data' => implode('<span class="pipe">|</span> ', $campus), 'class' => array('locations'));

            // Add to row.
            $rows[] = array('data' => $row, 'class' => array('main-education'));

            // Specializations of this education.
            $query = new EntityFieldQueryExtraFields();
              $specializations = $query->entityCondition('entity_type', 'node')
              ->propertyCondition('type', 'specialization')
              ->propertyCondition('status', 1)
              ->addExtraField('', 'title', 'title', 'node')
              ->addExtraField('field_campus', 'target_id', 'nid')
              ->fieldCondition('field_opleiding', 'target_id', $nid, '=')
              ->execute();

            if (!empty($specializations)) {
              foreach ($specializations['node'] as $snid => $sinfo) {

                $row = array();

                // Title.
                $row[] = array('data' => l($sinfo->extraFields->title, 'node/' . $snid), 'class' => array('education'));

                // Campus.
                $campus = array();
                if (!empty($sinfo->extraFields->field_campus_nid)) {
                  if (is_array($sinfo->extraFields->field_campus_nid)) {
                    foreach ($sinfo->extraFields->field_campus_nid as $cid) {
                      if (is_array($cid)) {
                        foreach ($cid as $cid_a) {
                          $campus[] = l($campus_records[$cid_a], 'node/' . $cid_a);
                        }
                      }
                      else {
                        $campus[] = l($campus_records[$cid], 'node/' . $cid);
                      }
                    }
                  }
                  else {
                    $cid = $sinfo->extraFields->field_campus_nid;
                    $campus[] = l($campus_records[$cid], 'node/' . $cid);
                  }
                  $row[] = array('data' => implode('<span class="pipe">|</span> ', $campus), 'class' => array('locations'));
                }
                $rows[] = $row;
              }
            }
          }
        }

        if (!empty($rows)) {

          // Add subtitle.
          if ($value == FOLLOW_UP_EDUCTION) {
            $content .= '<div class="grey-box">';
            $content .= '<h2>' . t('Follow up courses in this interest area') . '</h2>';
          }

          // Table.
          $variables = array(
            'rows' => $rows,
          );
          $content .= theme('table', $variables);

          // Add subtitle.
          if ($value == FOLLOW_UP_EDUCTION) {
            $content .= '</div>';
          }

        }
    }

  }

  if (!empty($content)) {

    $content = '<div class="education-on-interest">' . $content . '</div>';
    $block              = new stdClass();
    $block->module      = 'thomas_more';
    $block->subtype     = 'eductions_in_interest';
    $block->title       = '';
    $block->content     = $content;

    return $block;
  }
}

/**
 * Returns the administrative title.
 */
function thomas_more_educations_in_interest_content_type_admin_title($subtype, $conf) {
  return t('Educations in interest');
}

/**
 * Display the administrative information for the pane.
 */
function thomas_more_educations_in_interest_content_type_admin_info($subtype, $conf) {
  return t('Educations in interest');
}
