<?php

require_once BASE_DIR . '\api\connection_api.php';

function register_user_form($form, &$form_state){  
    $form['user_name'] = array(
      '#type' => 'textfield',
      '#title' => 'Digite seu nome',
      '#size' => 50,
      '#maxlength' => 40,
      '#required' => TRUE,
    );
  
    $form['user_email'] = array(
      '#type' => 'textfield',
      '#title' => 'Digite seu e-mail',
      '#size' => 50,
      '#maxlength' => 50,
      '#required' => TRUE,
    );

    $form['user_type'] = array(
      '#type' => 'select',
      '#title' => 'Digite o tipo da conta',
      '#options' => array(t('Discente'), t('Docente')),
      '#required' => TRUE,
    );
  
    $form['user_password'] = array(
      '#type' => 'password',
      '#title' => 'Digite sua senha',
      '#size' => 50,
      '#maxlength' => 64,
      '#required' => TRUE,
    );
  
    $form['user_submit_button'] = array(
      '#type' => 'submit',
      '#value' => t('Enviar'),
      '#attributes' => array("onclick" => "javascript: this.value='Enviando...'; this.disabled = true; this.form.submit();"),
    );
    
    return $form;
  }

function table_user_form($form, &$form_state){
  $sample_data = json_decode(get_all_users()->data, TRUE);

  $form['user_search'] = array(
    '#type' => 'textfield',
    '#title' => 'Digite sua busca',
    '#size' => 30,
    '#maxlength' => 50,
  );
  
  $form['search_user_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Pesquisar'),
    '#name' => 'user_search',
    '#submit' => array('crud_user_form_search_user_submit'),
    '#attributes' => array("onclick" => "javascript: this.value='Pesquisando...'; this.disabled = true; this.form.submit();"),
  );

  $sample_header = array(
      'name' => t('Name'),
      'email' => t('E-mail'),
      'type' => t('Type'),
  );

  $options = array();
  if ($sample_data['sucess']){
    foreach ($sample_data['data'] as $data) {
      $options[$data['id']] = array(
          'name' => $data['name'],
          'email' => $data['email'],
          'type' => $data['type'],
      );
    }
  }

  $form['table'] = array(
      '#type' => 'tableselect',
      '#header' => $sample_header,
      '#options' => $options,
      '#empty' => t($sample_data['message']),
  );

  $form['delete_user_submit'] = array(
      '#type' => 'submit',
      '#value' => t('Excluir usuário'),
      '#name' => 'delete_user',
      '#submit' => array('crud_user_form_delete_user_submit'),
  );

  return $form;
}
