<?php

/**
 * @file
 * Plugin to show testimonials - depending on context also.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Homepage quicklinks'),
  'defaults' => array(),
  'category' => t('Thomas More'),
);

/**
 * The configuration form..
 */
function thomas_more_home_quicklinks_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Output function for the 'testimonials' block.
 */
function thomas_more_home_quicklinks_content_type_render($subtype, $conf, $panel_args) {
  $content = '';
  $content .= '<div id="quicklinks">';
  $content .= '<a href="#opleidingen" id="educations"><div class="icon"><img src="/'. drupal_get_path('theme', 'wundertheme'). '/images/icons/home_quick_links/opleidingen.png" /></div>Bekijk onze opleidingen</a>';
  $content .= '<a href="#infodagen" id="infodays"><div class="icon"><img src="/'. drupal_get_path('theme', 'wundertheme'). '/images/icons/home_quick_links/infodagen.png" /></div>Infodagen &amp; openlesdagen</a>';
  $content .= '<a href="#campussen" id="campusses"><div class="icon"><img src="/'. drupal_get_path('theme', 'wundertheme'). '/images/icons/home_quick_links/campussen.png" /></div>Ontdek onze campussen</a>';
  //$content .= '<a href="#getuigenissen" id="testimonials"><div class="icon"><img src="/'. drupal_get_path('theme', 'wundertheme'). '/images/icons/home_quick_links/getuigenissen.png" /></div>Studenten getuigen</a>';
  $content .= '<a href="#nieuws" id="news" class="last"><div class="icon"><img src="/'. drupal_get_path('theme', 'wundertheme'). '/images/icons/home_quick_links/nieuws.png" /></div>Nieuws &amp; evenementen</a>';
  $content .= '</div>';

  $block              = new stdClass();
  $block->module      = 'thomas_more';
  $block->subtype     = 'quicklinks';
  $block->title       = '';
  $block->content     = $content;
  return $block;
}

/**
 * Returns the administrative title.
 */
function thomas_more_home_quicklinks_content_type_admin_title($subtype, $conf) {
  return t('Homepage quicklinks');
}

/**
 * Display the administrative information for the pane.
 */
function thomas_more_home_quicklinks_content_type_admin_info($subtype, $conf) {
  return t('Homepage quicklinks');
}
