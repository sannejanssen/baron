<?php

/**
 * @file
 * Implementation for the main pages.
 */

// Plugin definition
$plugin = array(
  'title' => t('Baron homepage layout'),
  'category' => t('Baron'),
  'theme' => 'homepage',
  'icon' => 'homepage.png',
  'css' => 'homepage.css',
  'regions' => array(
    'row_events' => t('Events'),
    'row_social' => t('Social'),
    'row_pictures' => t('Pictures'),
    'row_videos' => t("Video's"),
    'row_contact' => t('Contact'),
  ),
);
