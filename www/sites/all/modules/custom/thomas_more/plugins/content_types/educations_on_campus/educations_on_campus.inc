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
  'title' => t('Educations on this campus block'),
  'defaults' => array(),
  'category' => t('Thomas More'),
);

/**
 * Output function for the educations on this campus block.
 */
function thomas_more_educations_on_campus_content_type_render($subtype, $conf, $panel_args) {
  $content = '';
  $node = menu_get_object();

  if ($node && $node->type == 'campus') {

    foreach (array(MAIN_EDUCATION, FOLLOW_UP_EDUCTION) as $value) {
      $query = new EntityFieldQueryExtraFields();
      $main_courses = $query->entityCondition('entity_type', 'node')
        ->propertyCondition('type', 'education')
        ->propertyCondition('status', 1)
        ->addExtraField('', 'title', 'title', 'node')
        ->addExtraField('field_campus', 'target_id', 'nid')
        ->fieldCondition('field_vervolgopleiding', 'value', $value, '=')
        ->fieldCondition('field_campus', 'target_id', $node->nid)
        ->propertyOrderBy('title', 'ASC')
        ->execute();

        $rows = array();

        if (!empty($main_courses)) {
          foreach ($main_courses['node'] as $nid => $info) {
            $row = array();

            // Title.
            $row[] = array('data' => l(check_plain($info->extraFields->title), 'node/' . $info->nid), 'class' => array('education'));



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
              ->propertyOrderBy('title', 'ASC')
              ->execute();

            if (!empty($specializations)) {
              foreach ($specializations['node'] as $snid => $sinfo) {

                $row = array();

                // Title.
                $row[] = array('data' => l(check_plain($sinfo->extraFields->title), 'node/' . $snid), 'class' => array('education'));

                $rows[] = $row;
              }
            }
          }
        }
        if (!empty($rows)) {

          // Add subtitle.
          if ($value == FOLLOW_UP_EDUCTION) {
            $content .= '<div class="grey-box">';
            $content .= '<h2>' . t('Follow up courses on this campus') . '</h2>';
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

    $content = '<div class="education-on-campus">' . $content . '</div>';
    $block              = new stdClass();
    $block->module      = 'thomas_more';
    $block->subtype     = 'eductions_on_campus';
    $block->title       = 'Opleidingen op deze campus';
    $block->content     = $content;

    return $block;
  }
}

/**
 * Returns the administrative title.
 */
function thomas_more_educations_on_campus_content_type_admin_title($subtype, $conf) {
  return t('Educations on this campus');
}

/**
 * Display the administrative information for the pane.
 */
function thomas_more_educations_on_campus_content_type_admin_info($subtype, $conf) {
  return t('Educations on this campus');
}
